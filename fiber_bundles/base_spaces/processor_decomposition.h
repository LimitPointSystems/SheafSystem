
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class processor_decomposition

#ifndef PROCESSOR_DECOMPOSITION_H
#define PROCESSOR_DECOMPOSITION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
class id_block;
}

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A processor_decomposition of a mesh into overlapping, communicating processor scopes.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC processor_decomposition : public any
{

public:

  // =============================================================================
  // PROCESSOR_DECOMPOSITION FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  processor_decomposition();

  ///
  /// Copy constructor.
  ///
  processor_decomposition(const processor_decomposition& xother);

  ///
  /// Destructor.
  ///
  virtual ~processor_decomposition();

  ///
  /// Creates an instance for mesh xmesh.
  ///
  processor_decomposition(const base_space_poset& xmesh, const string& xname);

  ///
  /// The name of this decomposition.
  ///
  const string& name() const;

  ///
  /// The mesh poset containing this decomposition.
  ///
  const base_space_poset& mesh() const;

  ///
  /// The set of processor read scope members.
  ///
  const subposet& read_scopes() const;

  ///
  /// The set of processor write scope members.
  ///
  const subposet& write_scopes() const;

  ///
  /// The set of processor send scope members.
  ///
  const subposet& send_scopes() const;

  ///
  /// The scope set of type xscope_type (mutable version).
  ///
  subposet& scope_set(const string& xscope_type);

  ///
  /// The scope set of type xscope_type (const version).
  ///
  const subposet& scope_set(const string& xscope_type) const;

  ///
  /// The number of processors in this decomposition.
  ///
  int processor_ct() const;

  ///
  /// The name for the read scope associated
  /// with the processor with client id xp_id.
  ///
  string read_scope_name(const scoped_index& xp_id) const;

  ///
  /// The zones in the read scope of the processor with client id xp_id.
  ///
  void read_scope(const scoped_index& xp_id, id_block& xresult) const;

  ///
  /// Creates a read scope for the processor
  /// with client id xp_id containing zones xzones.
  ///
  scoped_index put_read_scope(const scoped_index& xp_id, id_block& xzones);

  ///
  /// The name for the write scope associated
  /// with the processor with client id xp_id.
  ///
  string write_scope_name(pod_index_type xp_id) const;

  ///
  /// The zones in the write scope of the processor with client id xp_id.
  ///
  void write_scope(const scoped_index& xp_id, id_block& xresult) const;

  ///
  /// Creates a write scope for the processor
  /// with client id xp_id containing zones xzones.
  ///
  scoped_index put_write_scope(const scoped_index& xp_id, id_block& xzones);

  ///
  /// The name for the send scope associated with
  /// the send processor with client id xsend_id and
  /// the receive processor with client id xrecv_id.
  ///
  string send_scope_name(const scoped_index& xsend_id,
			 const scoped_index& xrecv_id) const;

  ///
  /// The zones in the send scope of
  /// send processor xsend_id and receive processor xrecv_id.
  ///
  void send_scope(const scoped_index& xsend_id,
                  const scoped_index& xrecv_id,
                  id_block& xresult) const;

  ///
  /// Creates a send scope for send processor xsend_id and
  /// receive processor xrecv_id containing zones xzones.
  ///
  scoped_index put_send_scope(const scoped_index& xsend_id,
				const scoped_index& xrecv_id,
				id_block& xzones);

  ///
  /// Extracts the send processor id from send scope name xname.
  ///
  pod_index_type send_id(const string& xname) const;

  ///
  /// The name for the comm scope associated
  /// with the processor with client id xp_id.
  ///
  string comm_scope_name(pod_index_type xp_id) const;

  ///
  /// The name for the scope set of type xscope_type
  /// associated with decomposition name xdecomp_name.
  ///
  static string scope_set_name(const string& xscope_type, const string& xdecomp_name);

  ///
  /// The name for the scope set of type xscope_type
  /// associated with this decomposition.
  ///
  string scope_set_name(const string& xscope_type);

  ///
  /// True if xscope_type is a valid scope type.
  ///
  static bool is_valid_scope_type(const string& xscope_type);

  ///
  /// True if xname is a valid decomposition name.
  ///
  static bool is_valid_name(const string& xname);

  ///
  /// The prefix for valid decomposition names.
  ///
  static string name_prefix();


  ///
  /// Computes the comm scopes from the read and send scopes.
  ///
  void compute_comm_scopes();

  ///
  /// Computes the maximum coarsening of the zones that will
  /// serve as jims for the macro-scale sublattice.
  ///
  void compute_zone_ceiling();

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual processor_decomposition* clone() const;

  ///
  /// Assignment operator
  ///
  processor_decomposition& operator=(const processor_decomposition& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

private:

  ///
  /// The name of this decomposition.
  ///
  string _name;

  ///
  /// The mesh poset containing this decomposition.
  ///
  base_space_poset* _mesh;

  ///
  /// The set of processor read scope members.
  ///
  subposet _read_scopes;

  ///
  /// The set of processor write scope members.
  ///
  subposet _write_scopes;

  ///
  /// The set of processor send scope members.
  ///
  subposet _send_scopes;

  ///
  /// The number of processors in this decomposition.
  ///
  int _processor_ct;

  ///
  /// Initializes the scope set of type xscope_type.
  ///
  void initialize_scope_set(const string& xscope_type);

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
  
} // namespace fiber_bundle


#endif // ifndef PROCESSOR_DECOMPOSITION_H
