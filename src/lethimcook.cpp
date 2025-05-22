#include <dds/dds.hpp>
#include "StringMessage.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
  dds::domain::DomainParticipant participant(0);
  dds::topic::Topic<example::StringMessage> topic(participant, "StringTopic");

  dds::sub::Subscriber sub(participant);
  dds::sub::DataReader<example::StringMessage> reader(sub, topic);

  std::cout << "[lethimcook] Waiting for data...\n";
  std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for data

  auto samples = reader.take();
  if (samples.begin() != samples.end()) {
    std::cout << "[lethimcook] Received: " << samples.begin()->data().content() << std::endl;
  } else {
    std::cout << "[lethimcook] No data received.\n";
  }

  return 0;
}
