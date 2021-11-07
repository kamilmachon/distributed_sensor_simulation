#ifndef MOTOR_DRIVER_MQTT_CLIENT_H
#define MOTOR_DRIVER_MQTT_CLIENT_H

#include <iostream>
#include <iomanip>

#include <mqtt_client_cpp.hpp>

namespace mqtt
{

    class MqttClient
    {

    public:
        MqttClient(std::string client_id, std::string hostname = "127.0.0.1", std::string portname = "6500") : hostname_(hostname), portname_(portname)
        {
            client_ = MQTT_NS::make_sync_client(ioc_, hostname_, portname_);
            MQTT_NS::setup_log();

            client_->set_client_id(client_id);
            client_->set_clean_session(true);

            using packet_id_t = typename std::remove_reference_t<decltype(*client_)>::packet_id_t;

            client_->set_connack_handler([](bool sp, MQTT_NS::connect_return_code connack_return_code)
                                         { return true; });
            client_->set_close_handler(
                []()
                {
                });
            client_->set_error_handler(
                [](MQTT_NS::error_code ec)
                {
                });
            client_->set_puback_handler(
                [&](packet_id_t packet_id)
                {
                    client_->disconnect();
                    return true;
                });
            client_->set_pubrec_handler( 
                [](packet_id_t packet_id)
                {
                    return true;
                });
            client_->set_pubcomp_handler( 
                [&](packet_id_t packet_id)
                {
                    client_->disconnect();
                    return true;
                });
            client_->set_suback_handler( 
                [&](packet_id_t packet_id, std::vector<MQTT_NS::suback_return_code> results)
                {
                    return true;
                });
            client_->set_publish_handler(
                [&](MQTT_NS::optional<packet_id_t> packet_id,
                    MQTT_NS::publish_options pubopts,
                    MQTT_NS::buffer topic_name,
                    MQTT_NS::buffer contents)
                {
                    if (callbacks_.find(topic_name.to_string()) != std::end(callbacks_))
                    {
                        callbacks_[topic_name.to_string()](contents.to_string());
                    }

                    return true;
                });

            client_->connect();

            std::thread([this]
                        { ioc_.run(); }).detach();
        }

        void Subscribe(std::string topic, std::function<void(const std::string &)> callback)
        {
            client_->subscribe(topic, qos_);
            callbacks_[topic] = callback;
        }

        void Publish(std::string topic, const std::string &msg)
        {
            client_->publish(topic, msg, qos_);
        }

    private:
        std::shared_ptr<mqtt::callable_overlay<mqtt::sync_client<mqtt::tcp_endpoint<boost::asio::ip::tcp::socket, mqtt::strand>>>> client_;

        std::unordered_map<std::string, std::function<void(const std::string &)>> callbacks_;

        boost::asio::io_context ioc_;

        MQTT_NS::qos qos_ = MQTT_NS::qos::at_most_once; //TODO: Figure this out
        std::string hostname_;
        std::string portname_;
    };

}

#endif