#ifndef K3_RUNTIME_DISPATCH_H
#define K3_RUNTIME_DISPATCH_H

#include <map>
#include <string>

#include "Common.hpp"
#include "Context.hpp"
#include "Serialization.hpp"

namespace K3 {

    //------------
    // Dispatcher class
    //
    // Every trigger type must have a Dispatcher that can be inserted
    // in a queue
    class Dispatcher {
      public:
        virtual Value pack() const = 0;
        virtual void unpack(const Value &msg) = 0;
        virtual void call_dispatch(__k3_context&, int, const Address&) = 0;
        virtual Dispatcher* clone() = 0;
        virtual ~Dispatcher() {}
    };

    template<typename T>
    class ValDispatcher : public Dispatcher {
      public:
        ValDispatcher(const T& arg) : _arg(arg) {}
        ValDispatcher(T&& arg) : _arg(std::move(arg)) {}
        ValDispatcher() {}

        void unpack(const Value &msg) { _arg = std::move(*K3Serializer::unpack_yas<T>(msg)); }

        Dispatcher* clone() { return new ValDispatcher<T>(_arg); }

        Value pack() const { return K3Serializer::pack_yas<T>(_arg); }

        void call_dispatch(__k3_context& context, int trigger_id, const Address& src) {
	        context.__dispatch(trigger_id, static_cast<void*>(&_arg), src);
        }

        T _arg;
    };

    // template<typename T>
    // class RefDispatcher : public Dispatcher {
    //   public:

    //     RefDispatcher(const T& arg) : _arg(arg) {}
    //     RefDispatcher() {}

    //     void unpack(const Value &msg) { throw std::runtime_error("RefDispatcher cannot unpack"); }

    //     Dispatcher* clone() { return new RefDispatcher<T>(_func, _arg); }

    //     Value pack() const { return K3Serializer::pack<T>(_arg); }

    //     const T &_arg;
    // };

    // template<typename T>
    // class SharedDispatcher : public Dispatcher {
    //   public:

    //     SharedDispatcher(std::shared_ptr<T> arg) : _arg(arg) {}
    //     SharedDispatcher() {}

    //     void unpack(const Value &msg) { _arg = std::shared_ptr<T>(K3Serializer::unpack<T>(msg)); }

    //     Dispatcher* clone() { return new SharedDispatcher<T>(_func, _arg); }

    //     Value pack() const { return K3Serializer::pack<T>(*_arg); }

    //     std::shared_ptr<T> _arg;
    // };


    // A TriggerDispatch table maps trigger names to the corresponding generated TriggerWrapper
    // function.
    using TriggerDispatch = std::vector<std::tuple<std::shared_ptr<Dispatcher>, Identifier> >;

#ifndef MAIN_PROGRAM
    extern
#endif
    TriggerDispatch dispatch_table;

} // namespace K3
#endif
