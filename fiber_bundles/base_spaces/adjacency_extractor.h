
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class ADJACENCY_EXTRACTOR

#ifndef ADJACENCY_EXTRACTOR_H
#define ADJACENCY_EXTRACTOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_DFT_H
#include "poset_dft.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif
 
namespace sheaf
{
  class abstract_poset_member;
  class poset_member;
  class poset_state_handle;    
}

namespace fiber_bundle
{

using namespace sheaf;
  
///
/// A traverser to extract the conventional adjacency
/// information from the poset representation of a mesh.
///
/// @deprecated To be removed from the library.
///
class SHEAF_DLL_SPEC adjacency_extractor: public poset_dft
{

public:

  // CANONICAL INTERFACE

  // Default constructor
  // not currently supported
  // adjacency_extractor();

  ///
  /// Copy constructor
  ///
  ///
  adjacency_extractor(const adjacency_extractor& xother);

  ///
  /// Assignment operator
  ///
  ///
  adjacency_extractor& operator=(const adjacency_extractor& xother);

  ///
  /// Destructor
  ///
  ///
  ~adjacency_extractor();

  ///
  /// Class invariant, true if this is in a valid state
  ///
  ///
  virtual bool  invariant() const;

  // ADJACENCY_EXTRACTOR INTERFACE

  ///
  /// Constructor for traverser over members of xhost
  ///
  ///
  adjacency_extractor(const poset_state_handle* xhost,
		      const string& xlower_level_subposet_name = "__vertices",
		      const string& xupper_level_subposet_name = "__elements");

  ///
  /// Extract the lower level member ids,
  /// adjacency_cts and adjacency arrays
  /// for the down set of xanchor
  ///
  ///
 void extract(const abstract_poset_member* xanchor,
              int* xdomain_mbrs,
              int xdomain_mbrs_ub,
              int* xadjacency_cts,
              int xadjacency_cts_ub,
              int* xadjacency,
              int xadjacency_ub);

  ///
  /// Extract the adjacency_cts and adjacency arrays
  /// for the members of lower_level whose client ids
  /// are given in xdomain_mbrs
  ///
  ///
  void extract(const int* xdomain_mbrs,
               int xdomain_mbrs_ct,
               int* xadjacency_cts,
               int xadjacency_cts_ub,
               int* xadjacency,
               int xadjacency_ub);


  ///
  /// Count the number of entries needed in the adjacency array
  /// for down set of xanchor.
  ///
  ///
  void count(const abstract_poset_member* xanchor);

  ///
  /// Count the number of entries needed in the adjacency array.
  /// for the members of lower_level whose client ids
  /// are given in xdomain_mbrs.
  ///
  ///
  void count(const int* xdomain_mbrs, int xdomain_mbrs_ct);

  ///
  /// The total number of members in the domain
  /// visited by the last previous call to count or extract.
  /// Synonym for adjacency_cts_ct().
  ///
  ///
  inline int domain_mbrs_ct() const
  {
    return adjacency_cts_ct();
  } ;

  ///
  /// The total number of entries required in the xdomain_mbrs array
  /// for a call to extract(xanchor). Intended mostly for use in
  /// preconditions; use count(xanchor) followed by <>_ct() queries instead.
  ///
  ///
  inline int domain_mbrs_ct(const abstract_poset_member* xanchor)
  {
    count(xanchor);
    return adjacency_cts_ct();
  } ;

  ///
  /// The total number of entries in the adjacency_cts array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int adjacency_cts_ct() const
  {
    return _adjacency_cts_ct;
  } ;

  ///
  /// The total number of entries in the adjacency array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int adjacency_ct() const
  {
    return _adjacency_ct;
  } ;

  ///
  /// The total number of entries required in the adjacency array
  /// for a call to extract(int* xdomain_mbrs, int xdomain_mbrs_ct, ...).
  /// Intended mostly for use in preconditions; use count(xanchor)
  /// followed by <>_ct() queries instead.
  ///
  ///
  inline int adjacency_ct(const int* xdomain_mbrs, int xdomain_mbrs_ct)
  {
    count(xdomain_mbrs, xdomain_mbrs_ct);
    return adjacency_ct();
  } ;

  ///
  /// The lower_level subposet of host()
  ///
  inline const subposet& lower_level() const
  {
    return _lower_level;
  } ;

  ///
  /// True if the current lower_level is not nested within another lower_level
  /// Negative used as precondition of previsit_action because traversal
  /// algorithm will not handle hierachically nested lower_level
  ///
  ///
  inline bool is_nested_lower_level(const abstract_poset_member* xmbr) const
  {
    return _lower_level.contains_member(xmbr) && !_up_set.empty();
  };

  ///
  /// The upper_level subposet of host()
  ///
  inline const subposet& upper_level() const
  {
    return _upper_level;
  } ;


private:

  // Action to be taken at previsit position for each member

  void previsit_action(abstract_poset_member* xmbr);

  // Action to be taken at each link

  void link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr);

  // Action to be taken at postvisit position for each member

  void postvisit_action(abstract_poset_member* xmbr);

  // Subposet of lower_level in the mesh

  subposet _lower_level;

  // Upper level subposet in the mesh

  subposet _upper_level;

  // List to store up-set of current lower_level
  slist<int> _up_set;

  // true if above lower_level
  bool _above_lower_level;

  // The index of the first entry in _adjacency for
  // the current lower_level
  int _first_entry;

  // True if just counting, not actually extracting adjacency
  bool _extracting;

  // Adjacency counts array, upper bound, and current count
  int* _adjacency_cts;
  int  _adjacency_cts_ub;
  int  _adjacency_cts_ct;

  // Adjacency array, upper bound, and current count
  int* _adjacency;
  int  _adjacency_ub;
  int  _adjacency_ct;



};
 
} // namespace fiber_bundle

#endif // ifndef ADJACENCY_EXTRACTOR_H
