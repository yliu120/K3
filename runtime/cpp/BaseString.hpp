#ifndef K3_RUNTIME_BASESTRING_H
#define K3_RUNTIME_BASESTRING_H

#include <cstring>
#include <memory>
#include <vector>

#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>
#include <boost/functional/hash.hpp>

#include <yaml-cpp/yaml.h>
#include <rapidjson/document.h>
#include <csvpp/csv.h>

#include <Common.hpp>
#include <dataspace/Dataspace.hpp>

char* dupstr(const char*) throw ();

namespace K3 {

class base_string {
  public:
  // Constructors/Destructors/Assignment.
  base_string(): buffer(nullptr) {}

  base_string(const base_string& other): buffer(dupstr(other.buffer)) {}

  base_string(base_string&& other): base_string() {
    swap(*this, other);
  }

  base_string(const char* b): buffer(dupstr(b)) {}
  base_string(const std::string& s) : buffer(dupstr(s.c_str())) {}

  base_string(const char* from, std::size_t count): base_string() {
    if (from && count) {
      buffer = new char[count + 1];
      strncpy(buffer, from, count);
      buffer[count] = 0;
    }
  }

  ~base_string() {
    if (buffer) {
      delete [] buffer;
    }
    buffer = 0;
  }

  base_string& operator += (const base_string& other) {
    auto new_buffer = new char[length() + other.length() + 1];

    std::strcpy(new_buffer, (buffer ? buffer : ""));
    std::strcat(new_buffer, (other.buffer ? other.buffer : ""));

    if (buffer) {
      delete [] buffer;
    }

    buffer = new_buffer;

    return *this;
  }

  base_string& operator += (const char* other) {
    return *this += base_string(other);
  }

  base_string& operator =(const base_string& other) {
    base_string temp(other);
    swap(*this, temp);
    return *this;
  }

  base_string& operator =(base_string&& other) {
    swap(*this, other);
    return *this;
  }

  friend void swap(base_string& first, base_string& second) {
    using std::swap;
    swap(first.buffer, second.buffer);
  }

  // Conversions
  operator std::string() const {
    return std::string(buffer ? buffer : "");
  }

  // Accessors
  std::size_t length() const {
    if (buffer) {
      return strlen(buffer);
    }

    return 0;
  }

  const char* c_str() const {
    return buffer;
  }

  // Comparisons
  bool operator ==(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") == 0;
  }

  bool operator ==(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") == 0;
  }

  bool operator !=(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") != 0;
  }

  bool operator !=(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") != 0;
  }

  bool operator <=(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") <= 0;
  }

  bool operator <=(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") <= 0;
  }

  bool operator <(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") < 0;
  }

  bool operator <(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") < 0;
  }

  bool operator >=(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") >= 0;
  }

  bool operator >=(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") >= 0;
  }

  bool operator >(const base_string& other) const {
    return strcmp(buffer ? buffer : "", other.buffer ? other.buffer : "") > 0;
  }

  bool operator >(const char* other) const {
    return strcmp(buffer ? buffer : "", other ? other : "") > 0;
  }

  // Operations
  base_string substr(std::size_t from, std::size_t to) const {
    if (!buffer) {
      return base_string();
    }

    auto n = length();

    if (from > n) {
      from = n;
    }

    if (to > n) {
      to = n;
    }

    return base_string(buffer + from, to - from);
  }

  // Modifies this string.
  Seq<R_elem<string_impl>> splitString(const string_impl& splitter) {
    Seq<R_elem<string_impl>> results;
    if (!buffer) {
      return results;
    }

    R_elem<string_impl> rec;
    char * pch;
    pch = strtok (buffer, splitter.c_str());
    while (pch != NULL)
    {
      rec.elem = string_impl(pch);
      results.insert(rec);
      pch = strtok (NULL, splitter.c_str());
    }

    return results;
  }

  // Stream Operators
  friend std::ostream& operator <<(std::ostream& out, const K3::base_string& s) {
    if (s.buffer) {
      return out << s.c_str();
    }

    return out;
  }

  char* begin() const {
    return buffer;
  }

  char* end() const {
    return buffer + length();
  }

  template <class archive>
  void serialize(archive& a, const unsigned int) {
    std::size_t len;
    if (archive::is_saving::value) {
      len = length();
    }
    a& BOOST_SERIALIZATION_NVP(len);
    if (archive::is_loading::value) {
      // Possibly extraneous:
      // Buffer might always be null when loading
      // since this base_str was just constructed
      if (buffer) {
        delete[] buffer;
        buffer = 0;
      }

      if (len) {
        buffer = new char[len + 1];
        buffer[len] = 0;
      } else {
        buffer = 0;
      }
    }
    if (buffer) {
      a& boost::serialization::make_array(buffer, len);
    }
  }

  template <class archive>
  void serialize(archive& a) const {
    std::size_t len = length();
    a & len;
    if ( buffer ) {
      a.write(buffer, len);
    }
  }

  template <class archive>
  void serialize(archive& a) {
    std::size_t len;
    a & len;
    // Possibly extraneous:
    // Buffer might always be null when loading
    // since this base_str was just constructed
    if (buffer) {
      delete[] buffer;
      buffer = 0;
    }

    if (len) {
      buffer = new char[len + 1];
      buffer[len] = 0;
    } else {
      buffer = 0;
    }
    if ( buffer ) { a.read(buffer, len); }
  }

 private:
  char* buffer;
};

inline base_string operator + (base_string s, base_string const& t) {
  return s += t;
}

inline base_string operator + (base_string s, char const* t) {
  return s += t;
}

inline base_string operator + (char const* t, base_string const& s) {
  auto new_string = base_string(t);
  return new_string += s;
}

// Specializations for CSV parsing/writing, skipping the length field.
template <>
void base_string::serialize(csv::parser& a, const unsigned int);

template <>
void base_string::serialize(csv::writer& a, const unsigned int);

} // namespace K3

namespace JSON {
  template <> struct convert<K3::base_string> {
    template <class Allocator>
    static rapidjson::Value encode(const K3::base_string& from, Allocator& al) {
      Value v;
      if (from.c_str()) {
        v.SetString(from.c_str(), al);
      }
      else {
        v.SetString("", al);
      }
      return v;
    }

  };
}

namespace YAML {
  template <>
  struct convert<K3::base_string> {
    static Node encode(const K3::base_string& s) {
      Node node;
      node = std::string(s.c_str());
      return node;
    }

    static bool decode(const Node& node, K3::base_string& s) {
      try {
        auto t = node.as<std::string>();
        s = K3::base_string(t);
        return true;
      } catch (YAML::TypedBadConversion<std::string> e) {
        return false;
      }
    }
  };
}

// Turn off class information tracking in boost serialization for base_strings.
BOOST_CLASS_IMPLEMENTATION(K3::base_string, boost::serialization::object_serializable);

#endif
