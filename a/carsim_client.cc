#include <boost/asio.hpp> // socket library
#include <iostream>
#include <string>

using namespace std;

int main() {
  boost::asio::io_service iosev;
  boost::asio::ip::tcp::socket socket(iosev);
  boost::asio::ip::tcp::endpoint ep(
      boost::asio::ip::address_v4::from_string("127.0.0.1"), 8081);
  boost::system::error_code err;
  socket.connect(ep, err);
  if (err) {
    cout << boost::system::system_error(err).what() << endl;
    return -1;
  }
  cout << "write something" << endl;
  socket.write_some(boost::asio::buffer("hello world!\n", 13), err);
  if (err) {
    std::cout << boost::system::system_error(err).what() << std::endl;
    return -1;
  }

  char buf[128];
  cout << "read something" << endl;
  socket.read_some(boost::asio::buffer(buf), err);
  if (err) {
    std::cout << boost::system::system_error(err).what() << std::endl;
    return -1;
  }
  cout << buf << endl;

  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, err);
  if (err) {
    std::cout << boost::system::system_error(err).what() << std::endl;
    return -1;
  }
}
