#include <dds/dds.hpp>
#include "StringMessage.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
  dds::domain::DomainParticipant participant(0);
  dds::topic::Topic<example::StringMessage> topic(participant, "StringTopic");

  dds::pub::Publisher pub(participant);
  dds::pub::DataWriter<example::StringMessage> writer(pub, topic);

  example::StringMessage msg;
  msg.content("Let him cook!");

  std::this_thread::sleep_for(std::chrono::seconds(1)); // allow discovery
  writer.write(msg);

  std::cout << "[yapper] Sent: " << msg.content() << std::endl;
  return 0;
}
