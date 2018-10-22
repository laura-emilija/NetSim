#include "network.h"
#include "random.h"


/*! Resizes the list of nodes (\ref values) */
void network::resize(const size_t&)
{

}
//-------------------------------------------------------------------
/*! Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes
  @param[out] success the link was succesfully inserted
 */
bool network::add_link(const size_t& a, const size_t& b);
{
  links[a] = b;
  links[b] = a;

  if(links[a] == b && links[b] ==a)
    return true;

  return false;
}
//---------------------------------------------------------------------
/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen) where *degree(n)* is Poisson-distributed.

  All previous links are cleared first.
  @param mean_deg the average of the Poisson distribution.
 */
size_t network::random_connect(const double&){

//clear map & std::vector<> v;

//use randomly

//return

//return
}

//-----------------------------------------
/*! Resets all node values.
  @param[in] vector of new node values
  @param[out] number of nodes succesfully reset
 */
size_t network::set_values(const std::vector<double>& v){
  size_t count(0);
  for(size_t i(0) ; i < v.size() ; ++i){
    if(add_link( i, std::vector[i]))
      ++ count;
  }
  return count;
}

//-------------------------------------------------
/*! Number of nodes */
size_t network::size() const{
  return map.size();
}

//-------------------------------------
/*! Degree (number of links) of node no *n* */
size_t network::degree(const size_t &_n) const{

}

//---------------------------------------
/*! Value of node no *n* */
double network::value(const size_t &_n) const{

}

//------------------------------------------
/*! All node values in descending order */
std::vector<double> network::sorted_values() const{
  //algorithme sorting ??
  // or vector[i] = map[i] ??
  //check si existe déja
}

//---------------------------------
/*! All neighbors (linked) nodes of node no *n* */
std::vector<size_t> network::neighbors(const size_t&) const{



}
