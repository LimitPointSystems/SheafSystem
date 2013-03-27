// $RCSfile: equivalence_relation.h,v $ $Revision: 1.21 $ $Date: 2013/01/12 17:17:40 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class equivalence_relation

#ifndef EQUIVALENCE_RELATION_H
#define EQUIVALENCE_RELATION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{
  
// Forward declarations to support friend delcaration.

template <typename T>
class equivalence_relation;

///
/// Inserts equivalence_relation xer into ostream xos.
///
template <typename T>
ostream&
operator<<(ostream& xos, const equivalence_relation<T>& xer);


///
/// An equivalence relation induced by a partition
/// of an implicit host set objects of type T.
/// The host set is not explicitly represented.
///
template <typename T>
class equivalence_relation : public any
{

  friend ostream & operator << <T> (ostream &xos, const equivalence_relation<T>& xer);

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual equivalence_relation* clone() const;

  ///
  /// Assignment operator
  ///
  ///
  equivalence_relation& operator=(const equivalence_relation& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // EQUIVALENCE_RELATION FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  ///
  equivalence_relation();

  ///
  /// Copy constructor
  ///
  ///
  equivalence_relation(const equivalence_relation& xother);

  ///
  /// Destructor
  ///
  virtual ~equivalence_relation();


  ///
  /// True if xmbr_id is the representative member of its equivalence class.
  ///
  bool contains_representative(const T& xmbr_id) const;


  ///
  /// True if xrep_id is the only member of its equivalence class;
  /// there are no other members that are equivalent to xmbr_id.
  ///
  bool contains_unique_representative(const T& xrep_id) const;


  ///
  /// True if xmbr_id is equivalent to xother_mbr_id
  ///
  bool contains_equivalence(const T& xmbr_id, const T& xother_mbr_id) const;

  ///
  /// Inserts member xmbr_id into the equivalence class
  /// represented by xrep_id.
  ///
  void insert_equivalence(const T& xmbr_id, const T& xrep_id);


  ///
  /// Deletes member xmbr_id from its equivalence class.
  /// (Self-equivalence can not be deleted.)
  ///
  void delete_equivalence(const T& xmbr_id);


  ///
  /// The representative member of the equivalence class containing member xmbr_id.
  ///
  T representative(const T& xmbr_id) const;


  ///
  /// The type of iterator for an equivalence class.
  ///
  typedef typename multimap<T, T>::const_iterator iterator_type;

  ///
  /// The type of iterator range for an equivalence class.
  ///
  typedef pair<iterator_type, iterator_type> range_type;

  ///
  /// An iterator range containing the other members of
  /// the equivalence class with representative xrep_id.
  /// The range does not include xrep_id itself.
  ///
  range_type equivalence_class(const T& xrep_id) const;

  ///
  /// An iterator range containing all the equivalences in this.
  ///
  range_type all_equivalences() const;


private:

  ///
  /// The type of the mbr to rep map.
  ///
  typedef hash_map<T, T> mbr_to_rep_type;

  ///
  /// A relation (a function in fact) from members to the standard
  /// representatives of the equivalence classes containing the members.
  ///
  mbr_to_rep_type _mbr_to_rep;

  ///
  /// The type of the rep to mbr map.
  ///
  typedef multimap<T, T> rep_to_mbr_type;

  ///
  /// A relation from standard representatives to members;
  /// the transpose of _mbr_to_rep.
  ///
  rep_to_mbr_type _rep_to_mbr;

};

// NON-MEMBER FUNCTIONS

///
/// Inserts the equivalence class defined by
/// equivalence_relation::range_type xrange
/// into ostream xos.
///
template <typename T>
ostream&
operator<<(ostream& xos, const typename equivalence_relation<T>::range_type& xrange);
 
} // namespace sheaf

#endif // ifndef EQUIVALENCE_RELATION_H
