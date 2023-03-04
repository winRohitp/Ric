#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

const std::string RIC_GNODEB_HOST = "localhost";
const uint16_t RIC_GNODEB_PORT = 8080;

int main()
{
  boost::asio::io_context io_context;

  udp::socket socket(io_context, udp::endpoint(udp::v4(), 0));

  udp::resolver resolver(io_context);
  udp::endpoint endpoint = *resolver.resolve({udp::v4(), RIC_GNODEB_HOST, std::to_string(RIC_GNODEB_PORT)});

  std::string message = "Hello from RIC Gnode B side!";

  socket.send_to(boost::asio::buffer(message), endpoint);

  return 0;
}
