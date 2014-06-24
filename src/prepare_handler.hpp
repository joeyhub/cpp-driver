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

#ifndef __CASS_PREPARE_HANDLER_HPP_INCLUDED__
#define __CASS_PREPARE_HANDLER_HPP_INCLUDED__

#include "response_callback.hpp"
#include "scoped_ptr.hpp"

namespace cass {

class RequestHandler;
class Message;

class PrepareHandler : public ResponseCallback {
public:
  PrepareHandler(RequestHandler* request_handler)
      : request_handler_(request_handler) {}

  bool init(const std::string& prepared_id);

  virtual Message* request() const { return request_.get(); }

  virtual void on_set(Message* response);

  virtual void on_error(CassError code, const std::string& message);

  virtual void on_timeout();

private:
  ScopedPtr<Message> request_;
  ScopedPtr<RequestHandler> request_handler_;
};

} // namespace cass

#endif
