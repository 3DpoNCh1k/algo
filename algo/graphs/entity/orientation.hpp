#pragma once

#include <sstream>
#include <string>

namespace algo::graphs::orientation {

struct Undirected {
  Undirected(int u, int v)
      : u(u),
        v(v){};

  int u;
  int v;

  bool operator==(const Undirected& that) {
    return (u == that.u && v == that.v) || (v == that.u && u == that.v);
  }

  int Neighbor(int w) {
    return w == u ? v : (w == v ? u : -1);
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Undirected: " << u << " <-> " << v;
    return ss.str();
  };
};

struct Directed {
  Directed(int from, int to)
      : from(from),
        to(to){};

  int from;
  int to;

  bool operator==(const Directed& that) {
    return from == that.from && to == that.to;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Directed: " << from << " -> " << to;
    return ss.str();
  };
};
}  // namespace algo::graphs::orientation
