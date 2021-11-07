#include <platform/Platform.h>

Platform::Platform(std::string hostname, std::string port)
    : mqtt_client_("Platform", hostname, port),
      hostname_(hostname), port_(port)
{
    cbuffer_.set_capacity(100);
}

void Platform::RegisterSensor(const std::string sensor_type, const uint64_t sensor_id, const std::string hostname, const std::string port)
{
    sensor_spawner_.RegisterSensor(sensor_type, sensor_id);
    mqtt_client_.Subscribe(sensor_type + '/' + std::to_string(sensor_id), std::bind(&Platform::MqttCallback, this, std::placeholders::_1));
}

void Platform::UnregisterSensor(const std::string sensor_type, const uint64_t sensor_id)
{
    sensor_spawner_.UnregisterSensor(sensor_type, sensor_id);
}

void Platform::MqttCallback(const std::string &msg)
{
    std::cout << "received mqtt message. buffer size = " << cbuffer_.size() << std::endl;
    std::lock_guard<std::mutex> lock(buffer_mutex_);
    cbuffer_.push_front(msg);
}

void Platform::RegisterUserCallback(std::function<void(boost::circular_buffer<std::string> &)> user_cb, const float rate)
{
    user_callback_ = user_cb;
    StartUserCallbackHandling(rate);
}

void Platform::StartUserCallbackHandling(const float rate)
{
    user_callback_rate_ = rate;
    user_callback_timer_ = std::make_unique<boost::asio::steady_timer>(io_service_, std::chrono::steady_clock::now() + boost::asio::chrono::milliseconds(static_cast<uint>(1.0 / rate * 1000)));
    user_callback_timer_->async_wait(std::bind(&Platform::HandleUserCallback, this));

    std::thread([this]
                { io_service_.run(); })
        .detach();
}

void Platform::HandleUserCallback()
{
    boost::circular_buffer<std::string> new_buffer;
    new_buffer.set_capacity(100);
    {
        std::lock_guard<std::mutex> lock(buffer_mutex_);
        cbuffer_.swap(new_buffer);
    }

    if (user_callback_)
    {
        user_callback_(new_buffer);
    }
    user_callback_timer_->expires_after(boost::asio::chrono::milliseconds(static_cast<uint>(1.0 / user_callback_rate_ * 1000)));
    user_callback_timer_->async_wait(std::bind(&Platform::HandleUserCallback, this));
}