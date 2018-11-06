#include "network.h"
#include "random.h"
#include <iostream>
#include <string>

void Network::resize(const size_t& n){
  values.resize(n);
  RNG.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b){

  if(a < values.size() && b < values.size() && a != b){
    auto range_a = links.equal_range(a);
    auto range_b = links.equal_range(b);

    for (auto i = range_a.first; i != range_a.second; ++i){
      for(auto j = range_b.first; j != range_b.second; ++j){
        if((i->first == j->second) && (j->first == i->second))
          return false;
      }
    }

    links.insert(std::make_pair(a, b));
    links.insert(std::make_pair(b, a));
    return true;
  }
  return false;
}

size_t Network::random_connect(const double& m){

  links.clear();
  std::vector <int> random_nodes;
  unsigned int degree(0);
  size_t max_size(values.size() -1);
  size_t count(0);

  for(size_t i(0); i<values.size(); ++i){
    degree = RNG.poisson(m);
    if(degree >= values.size()) degree = max_size;
    random_nodes.clear();
    random_nodes.resize(degree);
    RNG.uniform_int(random_nodes, 0,max_size);
    for(auto j : random_nodes){
      if(add_link(i, j)) ++count;
    }
  }
  return count;
}

size_t Network::set_values(const std::vector<double>& new_values){

  size_t nb_nodes(0);
  if(values.size() <= new_values.size()){
    nb_nodes = values.size();
  } else{
    nb_nodes = new_values.size();
  }

  for(size_t i(0); i < nb_nodes; ++i){
    values [i] = new_values [i];
  }

  return nb_nodes;
}

size_t Network::size() const
{  return values.size();}

size_t Network::degree(const size_t & n) const
{
  check_value(n);
  return links.count(n);
}

double Network::value(const size_t & n) const
{
  check_value(n);
  return values[n];
}

inline void Network::check_value(const size_t & n) const
{
  if(n >= values.size())
    throw std::string("Error: non existant node");
}

std::vector<double> Network::sorted_values() const{

  std::vector<double> sorted(values);
  std::sort(sorted.begin(), sorted.end(),std::greater<double>());
  return sorted;
}

std::vector<size_t> Network::neighbors(const size_t& n) const{

  std::vector<size_t> v;
  v.clear();
  auto range_n = links.equal_range(n);

  for(auto i = range_n.first; i != range_n.second; ++i){
    v.push_back(i->second);
  }

  return v;
}
