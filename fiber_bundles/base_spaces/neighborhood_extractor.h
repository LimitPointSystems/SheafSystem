// $RCSfile: neighborhood_extractor.h,v $ $Revision: 1.17 $ $Date: 2013/01/12 17:16:52 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class NEIGHBORHOOD_EXTRACTOR

#ifndef NEIGHBORHOOD_EXTRACTOR_H
#define NEIGHBORHOOD_EXTRACTOR_H

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
}

namespace fiber_bundle
{
  
  using namespace sheaf;
///
/// A traverser to extract the conventional neighborhood
/// information from the poset representation of a mesh.
///
/// @deprecated To be removed from the library.
///
class SHEAF_DLL_SPEC neighborhood_extractor: public poset_dft
{

public:

  // CANONICAL INTERFACE

  // Default constructor
  // not currently supported
  // neighborhood_extractor();

  ///
  /// Copy constructor
  ///
  ///
  neighborhood_extractor(const neighborhood_extractor& xother);

  ///
  /// Assignment operator
  ///
  ///
  neighborhood_extractor& operator=(const neighborhood_extractor& xother);

  ///
  /// Destructor
  ///
  ///
  ~neighborhood_extractor();

  ///
  /// Class invariant, true if this is in a valid state
  ///
  ///
  virtual bool  invariant() const;

  // NEIGHBORHOOD_EXTRACTOR INTERFACE

  ///
  /// Constructor for traverser to extract neighborhoods
  /// of members of upper level subposet which are linked
  /// by members of lower level subposet. If xincludes_center,
  /// the neighborhood includes its center, otherwise it
  /// includes only neighbors of the center.
  ///
  ///
  neighborhood_extractor(const poset_state_handle* xhost,
                         const string& xlower_level_subposet_name,
                         const string& xupper_level_subposet_name,
                         bool xincludes_center);

  ///
  /// Extract the lower level member ids,
  /// neighborhood_cts and neighborhood arrays
  /// for the down set of xanchor
  ///
  ///
  void extract(const abstract_poset_member* xanchor,
               int* xdomain_mbrs,
               int xdomain_mbrs_ub,
               int* xneighborhood_cts,
               int xneighborhood_cts_ub,
               int* xneighborhood,
               int xneighborhood_ub);

  ///
  /// Extract the neighborhood_cts and neighborhood arrays
  /// for the members of upper_level whose client ids
  /// are given in xdomain_mbrs
  ///
  ///
  void extract(const int* xdomain_mbrs,
               int xdomain_mbrs_ub,
               int* xneighborhood_cts,
               int xneighborhood_cts_ub,
               int* xneighborhood,
               int xneighborhood_ub);


  ///
  /// Count the number of entries needed in the neighborhood array
  /// for down set of xanchor.
  ///
  ///
  void count(const abstract_poset_member* xanchor);

  ///
  /// Count the number of entries needed in the neighborhood array.
  /// for the members of upper_level whose client ids
  /// are given in xdomain_mbrs.
  ///
  ///
  void count(const int* xdomain_mbrs, int xdomain_mbrs_ub);

  ///
  /// True if neighborhood includes its "center";
  /// false if neighborhood includes only the neighbors of the center.
  ///
  ///
  inline bool includes_center() const
  {
    return _includes_center;
  } ;

  ///
  /// The total number of members in the upper_level
  /// visited by the last previous call to count or extract.
  /// Synonym for neighborhood_cts_ct().
  ///
  ///
  inline int domain_mbrs_ct() const
  {
    return neighborhood_cts_ct();
  } ;

  ///
  /// The total number of entries required in the domain_mbrs array
  /// for a call to extract(xanchor). Intended mostly for use in
  /// preconditions; use count(xanchor) followed by <>_ct() queries instead.
  ///
  ///
  inline int domain_mbrs_ct(const abstract_poset_member* xanchor)
  {
    count(xanchor);
    return neighborhood_cts_ct();
  } ;

  ///
  /// The total number of entries in the neighborhood_cts array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int neighborhood_cts_ct() const
  {
    return _neighborhood_cts_ct;
  } ;

  ///
  /// The total number of entries in the neighborhood array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int neighborhood_ct() const
  {
    return _neighborhood_ct;
  } ;

  ///
  /// The total number of entries required in the neighborhood array
  /// for a call to extract(int* xdomain_mbrs, int xdomain_mbrs_ub, ...).
  /// Intended mostly for use in preconditions; use count(xanchor)
  /// followed by <>_ct() queries instead.
  ///
  ///
  inline int neighborhood_ct(const int* xdomain_mbrs, int xdomain_mbrs_ub)
  {
    count(xdomain_mbrs, xdomain_mbrs_ub);
    return neighborhood_ct();
  } ;

  ///
  /// The lower_level subposet of host()
  ///
  inline const subposet& lower_level() const
  {
    return _lower_level;
  } ;

  ///
  /// True if the current upper_level is not nested within another upper_level
  /// Negative used as precondition of previsit_action because traversal
  /// algorithm will not handle hierachically nested upper_level
  ///
  ///
  inline bool is_nested_upper_level(const abstract_poset_member* xmbr) const
  {
    return _upper_level.contains_member(xmbr) && !_down_set.empty();
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

  // List to store strict down-set of current upper_level
  slist<int> _down_set;

  // List to store non-strict up-set of current lower_level
  slist<int> _up_set;

  // true if below upper_level
  bool _below_upper_level;

  // visited markers for down and up set portions of traversal
  zn_to_bool*   _down_set_visited;
  zn_to_bool*   _up_set_visited;

  // The index of the first entry in _neighborhood for
  // the current upper_level
  int _first_entry;

  // True if just counting, not actually extracting neighborhood
  bool _extracting;

  // True if neighborhood includes its "center";
  // False if nieghborhood includes only the neighbors of the center.
  bool _includes_center;

  // The index of the current member of the upper level
  int _center;

  // Neighborhood counts array, upper bound, and current count
  int* _neighborhood_cts;
  int  _neighborhood_cts_ub;
  int  _neighborhood_cts_ct;

  // Neighborhood array, upper bound, and current count
  int* _neighborhood;
  int  _neighborhood_ub;
  int  _neighborhood_ct;

};
  
} // namespace fiber_bundle

#endif // ifndef NEIGHBORHOOD_EXTRACTOR_H
