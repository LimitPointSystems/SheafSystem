// $RCSfile: connectivity_extractor.h,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:16:51 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class CONNECTIVITY_EXTRACTOR

#ifndef CONNECTIVITY_EXTRACTOR_H
#define CONNECTIVITY_EXTRACTOR_H

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
/// A traverser to extract the conventional connectivity
/// information from the poset representation of a mesh.
///
/// @deprecated To be removed from the library.
///
class SHEAF_DLL_SPEC connectivity_extractor: public poset_dft
{

public:

  // CANONICAL INTERFACE

  // Default constructor
  // not currently supported
  // connectivity_extractor();

  ///
  /// Copy constructor
  ///
  ///
  connectivity_extractor(const connectivity_extractor& xother);

  ///
  /// Assignment operator
  ///
  ///
  connectivity_extractor& operator=(const connectivity_extractor& xother);

  ///
  /// Destructor
  ///
  ///
  ~connectivity_extractor();

  ///
  /// Class invariant, true if this is in a valid state
  ///
  ///
  virtual bool  invariant() const;

  // CONNECTIVITY_EXTRACTOR INTERFACE

  ///
  /// Constructor for traverser over members of xhost
  ///
  ///
  connectivity_extractor(const poset_state_handle* xhost,
                         const string& xlower_level_subposet_name,
                         const string& xupper_level_subposet_name);
  //                      bool no_edges = true);

  ///
  /// Extract the lower level member ids,
  /// connectivity_cts and connectivity arrays
  /// for the down set of xanchor
  ///
  ///
  void extract(const abstract_poset_member* xanchor,
               int* xdomain_mbrs,
               int xdomain_mbrs_ub,
               int* xconnectivity_cts,
               int xconnectivity_cts_ub,
               int* xconnectivity,
               int xconnectivity_ub);

  ///
  /// Extract the connectivity_cts and connectivity arrays
  /// for the members of upper_level whose client ids
  /// are given in xdomain_mbrs
  ///
  ///
  void extract(const int* xdomain_mbrs,
               int xdomain_mbrs_ub,
               int* xconnectivity_cts,
               int xconnectivity_cts_ub,
               int* xconnectivity,
               int xconnectivity_ub);


  ///
  /// Count the number of entries needed in the connectivity array
  /// for down set of xanchor.
  ///
  ///
  void count(const abstract_poset_member* xanchor);

  ///
  /// Count the number of entries needed in the connectivity array.
  /// for the members of upper_level whose client ids
  /// are given in xdomain_mbrs.
  ///
  ///
  void count(const int* xdomain_mbrs, int xdomain_mbrs_ub);

  ///
  /// The total number of members in the upper_level
  /// visited by the last previous call to count or extract.
  /// Synonym for connectivity_cts_ct().
  ///
  ///
  inline int domain_mbrs_ct() const
  {
    return connectivity_cts_ct();
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
    return connectivity_cts_ct();
  } ;

  ///
  /// The total number of entries in the connectivity_cts array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int connectivity_cts_ct() const
  {
    return _connectivity_cts_ct;
  } ;

  ///
  /// The total number of entries in the connectivity array
  /// determined by the last previous call to count or extract.
  ///
  ///
  inline int connectivity_ct() const
  {
    return _connectivity_ct;
  } ;

  ///
  /// The total number of entries required in the connectivity array
  /// for a call to extract(int* xdomain_mbrs, int xdomain_mbrs_ub, ...).
  /// Intended mostly for use in preconditions; use count(xanchor)
  /// followed by <>_ct() queries instead.
  ///
  ///
  inline int connectivity_ct(const int* xdomain_mbrs, int xdomain_mbrs_ub)
  {
    count(xdomain_mbrs, xdomain_mbrs_ub);
    return connectivity_ct();
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

  // Method to check for need to swap nodes in
  // triangle and quad elements
  // (See notes in previsit_action and postvisit_action).

  bool check_element_types() const;

  // Subposet of lower_level in the mesh

  subposet _lower_level;

  // Upper level subposet in the mesh

  subposet _upper_level;

  // List to store down-set of current upper_level
  slist<int> _down_set;

  // true if above upper_level
  bool _below_upper_level;

  // True if extracting nodal connectivity
  bool _nodal_connectivity;

  // True if first boundary segment has negative orientation
  bool _first_bdy_seg_reversed;

  // The index of the first entry in _connectivity for
  // the current upper_level
  int _first_entry;

  // True if just counting, not actually extracting connectivity
  bool _extracting;

  // Connectivity counts array, upper bound, and current count
  int* _connectivity_cts;
  int  _connectivity_cts_ub;
  int  _connectivity_cts_ct;

  // Connectivity array, upper bound, and current count
  int* _connectivity;
  int  _connectivity_ub;
  int  _connectivity_ct;

};

} // namespace fiber_bundle

#endif // ifndef CONNECTIVITY_EXTRACTOR_H
