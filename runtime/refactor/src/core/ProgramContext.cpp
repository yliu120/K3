#include <iostream>
#include <memory>
#include <string>
#include <map>

#include "Common.hpp"
#include "core/Engine.hpp"
#include "core/ProgramContext.hpp"
#include "serialization/Codec.hpp"
#include "types/Message.hpp"
#include "types/Value.hpp"

namespace K3 {

ProgramContext::ProgramContext(Engine& e) : StandardBuiltins(e), __engine_(e) {}

void ProgramContext::__dispatch(SentinelValue* sv) {
  throw EndOfProgramException();
}

std::map<TriggerID, string> ProgramContext::__trigger_names_;

DummyContext::DummyContext(Engine& e) : ProgramContext(e) {
  state_ = make_shared<DummyState>();
}

// TODO(jbw) ensure we can move out of the as<> function
void DummyContext::__dispatch(NativeValue* nv, TriggerID t) {
  if (t == 1) {
    int i = *nv->as<int>();
    intTrigger(i);
  } else if (t == 2) {
    std::string s = std::move(*nv->as<std::string>());
    stringTrigger(s);
  } else {
    throw std::runtime_error("Invalid trigger ID");
  }
  return;
}

void DummyContext::__dispatch(PackedValue* pv, TriggerID t) {
  shared_ptr<NativeValue> nv;
  shared_ptr<Codec> codec;
  if (t == 1) {
    codec = Codec::getCodec<int>(pv->format());
  } else if (t == 2) {
    codec = Codec::getCodec<std::string>(pv->format());
  } else {
    throw std::runtime_error("Invalid trigger ID");
  }
  nv = codec->unpack(*pv);
  return __dispatch(nv.get(), t);
}

void DummyContext::__patch(const YAML::Node& node) {
  YAML::convert<DummyContext>::decode(node, *this);
}

unit_t DummyContext::processRole(const unit_t&) {
  if (role == "int") {
    MessageHeader h(me, me, 1);
    // TODO(jbw) grab internal format from NetworkManager
    static shared_ptr<Codec> codec =
        Codec::getCodec<int>(CodecFormat::BoostBinary);
    __engine_.send(h, make_shared<TNativeValue<int>>(5), codec);
  } else if (role == "string") {
    MessageHeader h(me, me, 2);
    static shared_ptr<Codec> codec =
        Codec::getCodec<std::string>(CodecFormat::BoostBinary);
    __engine_.send(h, make_shared<TNativeValue<std::string>>("hi"), codec);
  }

  return unit_t{};
}

void DummyContext::intTrigger(int i) {
  state_->my_int_ = i;
  return;
}

void DummyContext::stringTrigger(std::string s) {
  state_->my_string_ = s;
  return;
}

}  // namespace K3
