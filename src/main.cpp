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

  // Correct setter usage
  example::StringMessage msg;
  msg.content("Hello from IDL-generated type!");

  writer.write(msg);
  std::cout << "Sent: " << msg.content() << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  dds::sub::Subscriber sub(participant);
  dds::sub::DataReader<example::StringMessage> reader(sub, topic);

  auto samples = reader.take();
  if (samples.begin() != samples.end()) {
    std::cout << "Received: " << samples.begin()->data().content() << std::endl;
  } else {
    std::cout << "No data received." << std::endl;
  }

  return 0;
}
