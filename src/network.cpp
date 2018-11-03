#include "network.h"
#include "random.h"
#include <iostream>

//#include <algorithm>



/*!
    Resizes the list of nodes (\ref values) and also resets all values.
    After this function is called \ref values has size *n* and contains random numbers (normal distribution, mean=0, sd=1).
 */
void Network::resize(const size_t& n){
  values.resize(n);
  RNG.normal(values);
}


//-------------------------------------------------------------------
/*!
  Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes
  @param[out] success the link was succesfully inserted (true if both nodes exist and the link did not exist yet)
 */
bool Network::add_link(const size_t& a, const size_t& b)
{

  if(a < values.size() && b < values.size() && a != b) // if nodes a or B exist
  {
    // alredy linked
    auto range_a = links.equal_range(a);
    auto range_b = links.equal_range(b);

    for (auto i = range_a.first; i != range_a.second; ++i)
    {
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
//---------------------------------------------------------------------
/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen),
  where *degree(n)* is Poisson-distributed.
  All previous links are erased first.
  @param[in] mean_deg the average of the Poisson distribution,
  @param[out] number of links created.
 */
size_t Network::random_connect(const double& m){

  links.clear();
  std::vector <int> random_nodes;
  random_nodes.clear();
  int degree(0);
  size_t max_size(values.size() -1);
  size_t count(0);

  for(size_t i(0); i<values.size(); ++i){
    degree = RNG.poisson(m);
    random_nodes.clear();
    random_nodes.resize(degree);
    RNG.uniform_int(random_nodes, 0,max_size);
    for(auto j : random_nodes){
      if(add_link(i, j)) ++count;
    }
  }
  return count;
}

//-----------------------------------------
/*! Resets node values with a vector of *n* new values.
  If the current size is *s* and *n<s* then only the first *n* values are changed.
  If *n>s* then only *s* values are used.
  The internal \ref values vector keeps the same size.
  @param[in] vector of new node values,
  @param[out] number of nodes succesfully reset.
 */

size_t Network::set_values(const std::vector<double>& new_values){
  size_t count(0);
  if(values.size() <= new_values.size()){
    for(size_t i(0); i<values.size(); ++i)
      values[i] = new_values[i];
    count= values.size();
  } else {
      for(size_t j(0); j< new_values.size(); ++j)
        values[j] = new_values[j];
      count= new_values.size();
  }

  return count;

}

//-------------------------------------------------
/*! Number of nodes */
size_t Network::size() const{
  return values.size();
  //divisé par 2 ??
}

//-------------------------------------
/*! Degree (number of links) of node no *n* */
size_t Network::degree(const size_t & n) const{
  return links.count(n);
}

//---------------------------------------
/*! Value of node no *n* */
double Network::value(const size_t & n) const{
  return values[n];
}

//------------------------------------------
/*! All node values in descending order.
    \ref values is left unchanged by this operation.
 */
std::vector<double> Network::sorted_values() const{
  std::vector<double> sorted(values);

  std::sort(sorted.begin(), sorted.end(),std::greater<double>()); //and std::sort(sorted.begin(), sorted.end());
  return sorted;
}

//---------------------------------
/*! All neighbors (linked) nodes of node no *n* */
std::vector<size_t> Network::neighbors(const size_t& n) const{

  std::vector<size_t> v;
  v.clear();
  auto range_n = links.equal_range(n);

  for(auto i = range_n.first; i != range_n.second; ++i){
    v.push_back(i->second);
  }

  return v;
}
