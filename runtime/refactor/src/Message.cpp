#include "Message.hpp"

Message::Message(const Address& src, const Address& dst, TriggerID trig, unique_ptr<Value> val) {
  source_ = src;
  destination_ = dst;
  trigger_ = trig;
  value_ = std::move(val);
}

Address Message::source() const {
  return source_;
}

Address Message::destination() const {
  return destination_;
}

TriggerID Message::trigger() const {
  return trigger_;
}

Value* Message::value() const {
  if (value_) {
    return value_.get();
  } else {
    throw std::runtime_error("Message contains a null value pointer");
  }
}
