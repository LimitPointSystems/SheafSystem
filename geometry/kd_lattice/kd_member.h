

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_member

#ifndef KD_MEMBER_H
#define KD_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif
 

#ifndef KD_ENUMS_H
#include "kd_enums.h"
#endif 

namespace sheaf
{
  class namespace_poset;
}

namespace fiber_bundle
{
  class e3_lite;
};

  
namespace geometry
{

///
/// The type of row dof tuple for kd_member.
///
class SHEAF_DLL_SPEC kd_member_row_dofs_type
{
public:
  ///
  /// The base space dimension.
  ///
  int db;

  ///
  /// The cell type id.
  ///
  int type_id;

  ///
  /// The cell type name.
  ///
  const char * type_name;

  ///
  /// The refinement depth.
  ///
  int refinement_depth;

  ///
  /// The alignment.
  ///
  int alignment;
};
  
///
/// Abstract member in a kd_lattice.
///
class SHEAF_DLL_SPEC kd_member : public any
{

  // ===========================================================
  /// @name KD_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The row dof tuple type.
  ///
  typedef kd_member_row_dofs_type row_dofs_type;

  ///
  /// Destructor
  ///
  virtual ~kd_member();

  ///
  /// The kd_lattice this is a member of.
  ///
  const kd_lattice& host() const;

  ///
  /// The id of this member.
  ///
  const scoped_index& id() const;

  ///
  /// Sets id() to xid.
  ///
  void put_id(const scoped_index& xid);

  ///
  /// The name of this member.
  ///
  string name() const;

  ///
  /// The name of the member with id xid in kd_lattice xhost.
  ///
  static string name(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The type_id of this member.
  ///
  int type_id() const;

  ///
  /// The type_id of the member with id xid in kd_lattice xhost.
  ///
  static int type_id(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The type_name of this member.
  ///
  string type_name() const;

  ///
  /// The type_name of the member with id xid in kd_lattice xhost.
  ///
  static string type_name(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The alignment of this member.
  ///
  kd_alignment alignment() const;

  ///
  /// The alignment of the member with id xid in kd_lattice xhost.
  ///
  static kd_alignment alignment(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The aligment of this; int version faster than enum version.
  ///
  int int_alignment() const;

  ///
  /// The aligment of the member with id xid in kd_lattice xhost; 
  /// int version faster than enum version.
  ///
  static int int_alignment(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if this member is a leaf in the kd-tree.
  ///
  bool is_leaf() const;

  ///
  /// True if the member with id xid in kd_lattice xhost is a leaf in the kd-tree.
  ///
  static bool is_leaf(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// True if this member is a jim.
  ///
  bool is_jim() const;

  ///
  /// True if the member with id xid in kd_lattice xhost is a jim.
  ///
  static bool is_jim(const kd_lattice& xhost, const scoped_index& xid);

//   ///
//   /// The coordinate bounds for this member.
//   ///
//   virtual void coord_bounds(e3_lite& xlb, e3_lite& xub) const = 0;

//   ///
//   /// True if plane xp intersects this edge.
//   ///
//   virtual bool in_bounds(const kd_plane& xp) const = 0;

//   ///
//   /// Splits this member in two at the intersection with plane xp.
//   ///
//   virtual void refine(const kd_plane& xp, scoped_index xnew_ids[]) = 0;

  ///
  /// The maximum db for base space posets using the kd_member schema.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = 3};

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

protected:

  ///
  /// Default constructor.
  ///
  kd_member();

  ///
  /// Creates an unattached instance in xhost.
  ///
  kd_member(kd_lattice& xhost);

  ///
  /// Creates an instance attached to the member with id xid in xhost.
  ///
  kd_member(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_member(const kd_member& xother);

  ///
  /// The kd_lattice this is a member of.
  ///
  kd_lattice* _host;

  ///
  /// The id of this member.
  //
  scoped_index _id;

  ///
  /// The coordinate bounds for the box defined by vertices with ids xi0, xid1 in kd_lattice xhost.
  ///
  static void coord_bounds(const kd_lattice& xhost, const scoped_index& xid0, const scoped_index& xid1, e3_lite& xlb, e3_lite& xub);
  
  ///
  /// The row dofs for this member.
  ///
  row_dofs_type& row_dofs();
  
  ///
  /// The row dofs for the member with id xid in kd_lattice xhost.
  ///
  static row_dofs_type& row_dofs(kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// The row dofs for this member, const version.
  ///
  const row_dofs_type& row_dofs() const;
  
  ///
  /// The row dofs for the member with id xid in kd_lattice xhost.
  ///
  static const row_dofs_type& row_dofs(const kd_lattice& xhost, const scoped_index& xid);
  

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual kd_member* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Assignment operator
  ///
  kd_member& operator=(const kd_member& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_member& operator=(const any& xother);

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
// ///
// /// Insert kd_member& xn into ostream& xos.
// ///
// SHEAF_DLL_SPEC 
// ostream & operator << (ostream &xos, const kd_member& xn);

///
/// The deep size of kd_member& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_member& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_MEMBER_H
