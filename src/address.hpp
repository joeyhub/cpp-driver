/*
  Copyright 2014 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef __CASS_ADDRESS_HPP_INCLUDED__
#define __CASS_ADDRESS_HPP_INCLUDED__

#include <uv.h>
#include <string.h>
#include <string>

namespace cass {

class Address {
public:
  Address() { memset(&addr_, 0, sizeof(addr_)); }

  static bool from_string(const std::string& ip, int port,
                          Address* output = NULL);

  bool init(const struct sockaddr* addr);

  struct sockaddr* addr() {
    return reinterpret_cast<struct sockaddr*>(&addr_);
  }

  const struct sockaddr* addr() const {
    return reinterpret_cast<const struct sockaddr*>(&addr_);
  }

  struct sockaddr_in* addr_in() {
    return reinterpret_cast<sockaddr_in*>(&addr_);
  }

  const struct sockaddr_in* addr_in() const {
    return reinterpret_cast<const sockaddr_in*>(&addr_);
  }

  struct sockaddr_in6* addr_in6() {
    return reinterpret_cast<sockaddr_in6*>(&addr_);
  }

  const struct sockaddr_in6* addr_in6() const {
    return reinterpret_cast<const sockaddr_in6*>(&addr_);
  }

  int family() const { return addr()->sa_family; }

  int port() const;

  std::string to_string() const;

  int compare(const Address& a) const;

private:
  struct sockaddr_storage addr_;
};

inline bool operator<(const Address& a, const Address& b) {
  return a.compare(b) < 0;
}

inline bool operator==(const Address& a, const Address& b) {
  return a.compare(b) == 0;
}

} // namespace cass

#endif
