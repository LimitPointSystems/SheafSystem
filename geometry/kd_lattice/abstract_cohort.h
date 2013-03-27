// $RCSfile: abstract_cohort.h,v $ $Revision: 1.4 $ $Date: 2013/01/10 13:54:42 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class abstract_cohort

#ifndef ABSTRACT_COHORT_H
#define ABSTRACT_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif 

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif
   
#ifndef SUBPOSET_H
#include "subposet.h"
#endif
 
namespace sheaf
{
  class index_space_handle;
  class mutable_index_space_handle;
}

namespace fiber_bundle
{
  class base_space_poset;  
}


namespace geometry
{
  
///
/// An abstract group of poset members identified by a subposet, a gathered id space and
/// an arbitrary client-defined id space; base class for cohort hierarchy.
///
class SHEAF_DLL_SPEC abstract_cohort
{

  // ===========================================================
  /// @name ABSTRACT_COHORT FACET
  // ===========================================================
  //@{

public:

//   ///
//   /// Creates a abstract_cohort with name xname in  xhost.
//   ///
//   abstract_cohort(base_space_poset& xhost, const string& xname);

  ///
  /// Destructor
  ///
  virtual ~abstract_cohort();

  ///
  /// The host poset.
  ///
  base_space_poset& host();

  ///
  /// The host poset.
  ///
  const base_space_poset& host() const;
  
  ///
  /// The name,
  ///
  string name() const;

  ///
  /// The number of active members.
  ///
  size_type ct() const;

  ///
  /// True if and only if this contains the poset member with id xid;
  /// synonym for contains(xid.hub_pod()).
  ///
  bool contains(const scoped_index& xid) const;

  ///
  /// True if and only if this contains the poset member with id xid;
  /// synonym for sp().contains_member(xid).
  ///
  bool contains(pod_index_type xid) const;

//   ///
//   /// The subposet.
//   ///
//   subposet& sp();

  ///
  /// The subposet, const version.
  ///
  const subposet& sp() const;

//   ///
//   /// The id space.
//   ///
//   index_space& id_space();

  ///
  /// The id space, const version
  ///
  const mutable_index_space_handle& id_space() const;
  
  ///
  /// The name of the client id space,
  ///
  const string& client_id_space_name();

  ///
  /// The client id space.
  ///
  mutable_index_space_handle& client_id_space();

  ///
  /// The client id space, const version
  ///
  const mutable_index_space_handle& client_id_space() const;

  ///
  /// If true, give each member a standard name.
  ///
  static bool& auto_name_members();

  ///
  /// If true, report cts() to cout whenever 
  /// new_member or delete_member is called.
  ///
  static bool& auto_output_cts();

protected:

  ///
  /// Default constructor.
  ///
  abstract_cohort();

  ///
  /// The host poset.
  ///
  base_space_poset* _host;

  ///
  /// The subposet.
  ///
  subposet _sp;

  ///
  /// The id space.
  ///
  mutable_index_space_handle* _id_space;

  ///
  /// The client id space.
  ///
  mutable_index_space_handle* _client_id_space;

  ///
  /// The number of active members.
  ///
  size_type _ct;
  
  ///
  /// Creates the colection in xhost with name xname.
  ///
  void new_state(base_space_poset& xhost, const string& xname);
  
//   ///
//   /// Creates the collection in xhost with name xname and d_cells(xd).
//   ///
//   void new_state(base_space_poset& xhost, int xd);

  ///
  /// A standard name for the member with id xid.
  ///
  string member_name(const scoped_index& xid);
  
  ///
  /// Creates a standard name for the member with id xid.
  ///
  void name_member(const scoped_index& xid);  

  ///
  /// Removes the standard name for the member with id xid.
  ///
  void unname_member(const scoped_index& xid);

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert abstract_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, abstract_cohort& xn);
  
} // end namespace geometry

#endif // ifndef ABSTRACT_COHORT_H
