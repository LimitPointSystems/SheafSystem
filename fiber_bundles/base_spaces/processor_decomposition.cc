// $RCSfile: processor_decomposition.cc,v $ $Revision: 1.24 $ $Date: 2013/01/12 17:16:52 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class processor_decomposition

#include "processor_decomposition.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "error_message.h"
#include "hash_index_space_state.h"
#include "id_block.h"
#include "index_iterator.h"
#include "preorder_iterator.h"
#include "std_set.h"
#include "std_sstream.h"
#include "stl_scoped_index.h"
#include "tern.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// =============================================================================
// PROCESSOR_DECOMPOSITION FACET
// =============================================================================

///
fiber_bundle::processor_decomposition::
processor_decomposition()
{

  // Preconditions:


  // Body:

  _processor_ct = 0;
  _mesh = 0;

  //$$SCRIBBLE: Adding a nonempty string to keep
  //            invariant() from blowing an assertion.

  _name = "unknown";

  // Postconditions:

  ensure(!name().empty());
  ensure(invariant());
  ensure(processor_ct() == 0);

  // Exit:

  return;
}


///
fiber_bundle::processor_decomposition::
processor_decomposition(const processor_decomposition& xother)
{

  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::processor_decomposition::
~processor_decomposition()
{
  // Preconditions:


  // Body:

  _read_scopes.detach_from_state();
  _write_scopes.detach_from_state();
  _send_scopes.detach_from_state();


  // Postconditions:

  // Exit:

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

///
fiber_bundle::processor_decomposition::
processor_decomposition(const base_space_poset& xmesh, const string& xname)
{
  // Preconditions:

  require(is_valid_name(xname));
  require(xmesh.includes_processor_decomposition(xname) ?
          xmesh.state_is_read_accessible() :
          xmesh.state_is_read_write_accessible());

  // Body:

  bool old_xmesh_includes_processor_decomposition_xname =
    xmesh.includes_processor_decomposition(xname);

  _mesh = const_cast<base_space_poset*>(&xmesh);
  _name = xname;


  initialize_scope_set("read");
  initialize_scope_set("write");
  initialize_scope_set("send");


  _processor_ct =
    (old_xmesh_includes_processor_decomposition_xname ? _read_scopes.member_ct() : 0);

  // Postconditions:

  ensure(mesh().is_same_state(&xmesh));
  ensure(name() == xname);
  ensure(xmesh.includes_processor_decomposition(xname));
  ensure(processor_ct() == (old_xmesh_includes_processor_decomposition_xname ?
                            read_scopes().member_ct() : 0));


  return;
}


///
const string&
fiber_bundle::processor_decomposition::
name() const
{
  return _name;
}


///
const fiber_bundle::base_space_poset&
fiber_bundle::processor_decomposition::
mesh() const
{
  return *_mesh;
}

///
const sheaf::subposet&
fiber_bundle::processor_decomposition::
read_scopes() const
{
  return _read_scopes;
}

///
const sheaf::subposet&
fiber_bundle::processor_decomposition::
write_scopes() const
{
  return _write_scopes;
}

///
const sheaf::subposet&
fiber_bundle::processor_decomposition::
send_scopes() const
{
  return _send_scopes;
}

///
sheaf::subposet&
fiber_bundle::processor_decomposition::
scope_set(const string& xscope_type)
{
  subposet* result;

  // Preconditions:

  require(is_valid_scope_type(xscope_type));

  // Body:

  switch (xscope_type[0])
  {
  case 'r':
    result = &_read_scopes;
    break;
  case 'w':
    result = &_write_scopes;
    break;
  case 's':
    result = &_send_scopes;
    break;
  }

  // Postconditions:


  // Exit:

  return *result;
}

///
const sheaf::subposet&
fiber_bundle::processor_decomposition::
scope_set(const string& xscope_type) const
{
  const subposet* result;

  // Preconditions:

  require(is_valid_scope_type(xscope_type));

  // Body:

  switch (xscope_type[0])
  {
  case 'r':
    result = &_read_scopes;
    break;
  case 'w':
    result = &_write_scopes;
    break;
  case 's':
    result = &_send_scopes;
    break;
  }

  // Postconditions:


  // Exit:

  return *result;
}

///
int
fiber_bundle::processor_decomposition::
processor_ct() const
{
  return _processor_ct;
}


///
string
fiber_bundle::processor_decomposition::
read_scope_name(const scoped_index& xp_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::" << xp_id << "_read";

  // Postconditions:


  // Exit:

  return lstream.str();
}


///
void
fiber_bundle::processor_decomposition::
read_scope(const scoped_index& xp_id, id_block& xresult) const
{
  // Preconditions:

  require(mesh().state_is_read_accessible());
  require(mesh().contains_member(read_scope_name(xp_id)));
  require(xresult.is_member_hub_id_space());

  // Body:

  xresult.set_ct(0);
  xresult.reserve(1024); // Arbitrary, avoids many small reallocations.

  processor_decomposition* cthis = const_cast<processor_decomposition*>(this);
  base_space_member lscope(cthis->_mesh, read_scope_name(xp_id));
  preorder_iterator litr(static_cast<abstract_poset_member&>(lscope), cthis->_mesh->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());

    litr.truncate();
  }

  lscope.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
sheaf::scoped_index
fiber_bundle::processor_decomposition::
put_read_scope(const scoped_index& xp_id, id_block& xzones)
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());
  require(!mesh().contains_member(read_scope_name(xp_id)));
  require(xzones.is_member_hub_id_space());

  require_for_all(i, 0, xzones.ct(), mesh().contains_member(xzones[i]));

  // Body:

  define_old_variable(int old_processor_ct = _processor_ct);

  base_space_member lscope(_mesh, xzones.base(), xzones.ct(), tern::TRUE, false);

  lscope.put_name(read_scope_name(xp_id), true, false);
  scoped_index result = lscope.index();
  _read_scopes.insert_member(result);

  _read_scopes.id_space().insert(xp_id, result);

  lscope.detach_from_state();
  ++_processor_ct;

  // Postconditions:

  ensure(mesh().contains_member(result));
  ensure(mesh().member_name(result) == read_scope_name(xp_id));
  ensure(read_scopes().contains_member(result));
  ensure(processor_ct() == old_processor_ct + 1);

  // Exit:

  return result;
}

///
string
fiber_bundle::processor_decomposition::
write_scope_name(pod_index_type xp_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::" << xp_id << "_write";

  // Postconditions:


  // Exit:

  return lstream.str();
}

///
void
fiber_bundle::processor_decomposition::
write_scope(const scoped_index& xp_id, id_block& xresult) const
{
  // Preconditions:

  require(mesh().state_is_read_accessible());
  require(mesh().contains_member(write_scope_name(xp_id)));
  require(xresult.is_member_hub_id_space());

  // Body:

  xresult.set_ct(0);
  xresult.reserve(1024); // Arbitrary, avoids many small reallocations.

  processor_decomposition* cthis = const_cast<processor_decomposition*>(this);
  base_space_member lscope(cthis->_mesh, write_scope_name(xp_id));
  preorder_iterator litr(static_cast<abstract_poset_member&>(lscope), cthis->_mesh->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());

    litr.truncate();
  }

  lscope.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
sheaf::scoped_index
fiber_bundle::processor_decomposition::
put_write_scope(const scoped_index& xp_id, id_block& xzones)
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());
  require(!mesh().contains_member(write_scope_name(xp_id)));
  require(xzones.is_member_hub_id_space());

  require_for_all(i, 0, xzones.ct(), mesh().contains_member(xzones[i]));

  // Body:

  base_space_member lscope(_mesh, xzones.base(), xzones.ct(), tern::TRUE, false);

  lscope.put_name(write_scope_name(xp_id), true, false);
  scoped_index result = lscope.index();
  _write_scopes.insert_member(result);

  _write_scopes.id_space().insert(xp_id, result);

  lscope.detach_from_state();

  // Postconditions:

  ensure(mesh().contains_member(result));
  ensure(mesh().member_name(result) == write_scope_name(xp_id));
  ensure(write_scopes().contains_member(result));

  // Exit:

  return result;
}

///
string
fiber_bundle::processor_decomposition::
send_scope_name(const scoped_index& xsend_id, const scoped_index& xrecv_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::" << xsend_id << "_send_" << xrecv_id;

  // Postconditions:


  // Exit:

  return lstream.str();
}

///
void
fiber_bundle::processor_decomposition::
send_scope(const scoped_index& xsend_id,
           const scoped_index& xrecv_id,
           id_block& xresult) const
{
  // Preconditions:

  require(mesh().state_is_read_accessible());
  require(mesh().contains_member(send_scope_name(xsend_id, xrecv_id)));
  require(xresult.is_member_hub_id_space());

  // Body:

  xresult.set_ct(0);
  xresult.reserve(1024); // Arbitrary, avoids many small reallocations.

  processor_decomposition* cthis = const_cast<processor_decomposition*>(this);
  base_space_member lscope(cthis->_mesh, send_scope_name(xsend_id, xrecv_id));
  preorder_iterator litr(static_cast<abstract_poset_member&>(lscope), cthis->_mesh->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());

    litr.truncate();
  }

  lscope.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
sheaf::scoped_index
fiber_bundle::processor_decomposition::
put_send_scope(const scoped_index& xsend_id,
               const scoped_index& xrecv_id,
               id_block& xzones)
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());
  require(!mesh().contains_member(send_scope_name(xsend_id, xrecv_id)));
  require(xzones.is_member_hub_id_space());

  require_for_all(i, 0, xzones.ct(), mesh().contains_member(xzones[i]));

  // Body:

  base_space_member lscope(_mesh, xzones.base(), xzones.ct(), tern::TRUE, false);

  lscope.put_name(send_scope_name(xsend_id, xrecv_id), true, false);
  scoped_index result = lscope.index();
  _send_scopes.insert_member(result);
  lscope.detach_from_state();

  // Postconditions:

  ensure(mesh().contains_member(result));
  ensure(mesh().member_name(result) == send_scope_name(xsend_id, xrecv_id));
  ensure(send_scopes().contains_member(result));

  // Exit:

  return result;
}


///
string
fiber_bundle::processor_decomposition::
scope_set_name(const string& xscope_type, const string& xdecomp_name)
{
  // Preconditions:

  require(is_valid_scope_type(xscope_type));

  // Body:

  string result(xdecomp_name);
  result += "::" + xscope_type + "_scopes";

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::processor_decomposition::
send_id(const string& xname) const
{
  // Preconditions:


  // Body:

  string::size_type lidx1, lidx2;

  lidx1 = xname.find("::") + 2;
  lidx2 = xname.find("_", lidx1);
  string lsend_id_str(xname.substr(lidx1, lidx2-lidx1));

  stringstream lstream(lsend_id_str);

  pod_index_type result;

  lstream >> result;

  // Postconditions:


  // Exit:

  return result;
}


///
string
fiber_bundle::processor_decomposition::
comm_scope_name(pod_index_type xp_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::" << xp_id << "_comm";

  // Postconditions:


  // Exit:

  return lstream.str();
}

///
string
fiber_bundle::processor_decomposition::
scope_set_name(const string& xscope_type)
{
  // Preconditions:

  require(is_valid_scope_type(xscope_type));

  // Body:

  string result(scope_set_name(xscope_type, _name));

  // Postconditions:


  // Exit:

  return result;
}

///
bool
fiber_bundle::processor_decomposition::
is_valid_scope_type(const string& xscope_type)
{
  bool result;

  // Preconditions:


  // Body:

  result =
    (xscope_type == "read") || (xscope_type == "write") || (xscope_type == "send");

  // Postconditions:


  // Exit:

  return result;
}

///
bool
fiber_bundle::processor_decomposition::
is_valid_name(const string& xname)
{
  bool result;

  // Preconditions:


  // Body:

  result = (xname.find(name_prefix()) == 0);

  // Postconditions:


  // Exit:

  return result;
}

///
string
fiber_bundle::processor_decomposition::
name_prefix()
{

  // Preconditions:


  // Body:

  string result(poset_path::reserved_prefix() + "pd_");

  // Postconditions:


  // Exit:

  return result;
}

///
void
fiber_bundle::processor_decomposition::
compute_comm_scopes()
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());

  // Body:

  block<scoped_index> lwrite_expansion(4096);
  block<scoped_index> lcomm_expansion(128);

  base_space_member lscope(_mesh, TOP_INDEX);

  subposet& lzones = _mesh->elements();

  index_space_handle& lread_space = _read_scopes.id_space();
  index_space_handle& lsend_space = _send_scopes.id_space();

  index_iterator lread_itr = _read_scopes.indexed_member_iterator();
  while(!lread_itr.is_done())
  {
    scoped_index lread_index = lread_itr.index();

    pod_index_type lproc_id = lread_space.pod(lread_index);

    // cout << "read id: " << lread_index << " proc id: " << lproc_id << endl;

    lwrite_expansion.set_ct(0);
    lcomm_expansion.set_ct(0);

    lscope.attach_to_state(lread_index);
    preorder_iterator lscope_itr(lscope, DOWN, NOT_STRICT);
    while(!lscope_itr.is_done())
    {
      scoped_index lscope_index = lscope_itr.index();

      // cout << "scope mbr: " << lscope_index;


      if(_send_scopes.contains_member(lscope_index))
      {
        // This is a send scope for some processor,
        // so it is either a send scope or a recv scope
        // for the current processor. Put it in the comm expansion.

        // cout << " is send scope, adding to comm";

        lcomm_expansion.push_back(lscope_index);


        if(send_id(_mesh->member_name(lscope_index)) == lproc_id)
        {
          // This is a send scope for the current processor.
          // Put this scope in the write expansion.

          lwrite_expansion.push_back(lscope_index);

          // cout << " and write";

        }

        // Don't need to go deeper.

        lscope_itr.truncate();
      }
      else if(lzones.contains_member(lscope_index))
      {
        // This zone is in the read scope of the current processor,
        // but is not in any send scope, so it belongs in the write scope.
        // Put it in the write expansion.

        lwrite_expansion.push_back(lscope_index);

        // cout << " is zone, adding to write";

        // Don't need to go deeper.

        lscope_itr.truncate();
      }
      else
      {
        // Just continue to next member.

        // cout << " skipping";

        lscope_itr.next();
      }

      // cout << endl;
    }


    // Join the members of the comm expansion to
    // create the write scope for the current processor.

    base_space_member lcomm_scope(_mesh,
                                  lcomm_expansion.base(),
                                  lcomm_expansion.ct(),
                                  tern::TRUE,
                                  false);

    lcomm_scope.put_name(comm_scope_name(lproc_id), true, false);
    lcomm_scope.detach_from_state();


    // Join the members of the write expansion to
    // create the write scope for the current processor.

    base_space_member lwrite_scope(_mesh,
                                   lwrite_expansion.base(),
                                   lwrite_expansion.ct(),
                                   tern::TRUE,
                                   false);

    lwrite_scope.put_name(write_scope_name(lproc_id), true, false);
    lwrite_scope.detach_from_state();

    lread_itr.next();
  }

  // Clean up.

  lscope.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::processor_decomposition::
compute_zone_ceiling()
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());

  // Body:

  // Compute coarsest common refinement (CCR) of all the current decompositions:
  // Let Z be the set of zones and z1, z2 be members of Z.
  // Define z1 ~ z2 iff z1 and z2 have the same upper cover.
  // then ~ is an equivalence relation and the CCR is the quotient Z/~.
  // That is, ~ partitions Z into equivalence classes and each member of
  // the CCR corresponds to one of these equivalence classes.
  // So we have to find the equivalence classes (distinct upper covers)
  // and then sort the zones into them.

  /// @issue the following implementation is a simple first cut, but
  /// there are several efficiency issues associated with it. Explicitly
  /// constructing the equivalence classes in separate storage uses too much
  /// memory. Constructing the ccr members by explicit joins uses too much time
  /// for at least 2 reasons: (1) each join is going to initialize subposets,
  /// making the performance ccr.ct()*zones.ct() and (2) each join is going
  /// to examine the entire down set (e.g. edges and vertices) which is
  /// not necessary.

  /// @todo reimplement using traversal and direct link editing.

  // Allocate a map from upper covers to equivalence classes.

  typedef map<set<pod_index_type>, block<scoped_index> > ec_map_type;
  ec_map_type lec_map;


  // Iterate over the zones and construct the equivalence classes.

  subposet& lzones_sp = _mesh->elements();
  index_iterator lzones_itr = lzones_sp.indexed_member_iterator();
  while(!lzones_itr.is_done())
  {
    // Create a set containing the upper cover of the current zone.

    set<pod_index_type> luc_set;
    cover_set_iterator luc_itr(_mesh->cover_iterator(UPPER, lzones_itr.index()));
    while(!luc_itr.is_done())
    {
      luc_set.insert(luc_itr.item());
      luc_itr.next();
    }

    // Insert the current zone into the equivalence class of the upper cover.

    lec_map[luc_set].push_back(lzones_itr.index());

    lzones_itr.next();
  }
  lzones_sp.detach_from_state();

  // Now create the members of the ccr by joining the members
  // of each equivalence class.

  base_space_member lccr_mbr(_mesh->top()); // Any member will do.

  int lccr_ct = 0;
  ec_map_type::iterator lec_itr = lec_map.begin();
  while(lec_itr != lec_map.end())
  {
    block<scoped_index>& lec = lec_itr->second;
    lccr_mbr.new_jrm_state(lec.base(), lec.ct(), tern::FALSE, false);
    stringstream lstream;
    lstream << "__floor_" << lccr_ct++;
    lccr_mbr.put_name(lstream.str(), true, false);
    ++lec_itr;
  }
  lccr_mbr.detach_from_state();


  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

///
bool
fiber_bundle::processor_decomposition::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const processor_decomposition*>(other) != 0;

  // Postconditions:

  return result;
}

///
fiber_bundle::processor_decomposition*
fiber_bundle::processor_decomposition::
clone() const
{
  processor_decomposition* result;

  // Preconditions:

  // Body:

  result = new processor_decomposition();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::processor_decomposition&
fiber_bundle::processor_decomposition::
operator=(const processor_decomposition& xother)
{

  // Preconditions:


  // Body:

  _name         = xother._name;
  _mesh         = xother._mesh;
  _read_scopes  = xother._read_scopes;
  _write_scopes = xother._write_scopes;
  _send_scopes  = xother._send_scopes;
  _processor_ct = xother._processor_ct;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::processor_decomposition::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(processor_ct() >= 0);
    invariance(!name().empty());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}



// =============================================================================
// PRIVATE MEMBER FUNCTIONS FACET
// =============================================================================

///
void
fiber_bundle::processor_decomposition::
initialize_scope_set(const string& xscope_type)
{
  // Preconditions:

  require(is_valid_scope_type(xscope_type));
  require(mesh().includes_subposet(scope_set_name(xscope_type, name())) ?
          mesh().state_is_read_accessible() :
          mesh().state_is_read_write_accessible());

  // Body:

  subposet& lscope_set = scope_set(xscope_type);
  string lscope_set_name = scope_set_name(xscope_type, name());

  if(mesh().includes_subposet(lscope_set_name))
  {
    // Scope set already exists; just attach to it.

    lscope_set.attach_to_state(_mesh, lscope_set_name);
  }
  else
  {
    // Scope set doesn't exist yet; create them.

    lscope_set.new_state(_mesh, true, false);
    lscope_set.put_name(lscope_set_name, true, false);
    lscope_set.new_id_space("hash_index_space_state",
			    hash_index_space_state::make_arg_list(0));
  }


  // Postconditions:

  ensure(mesh().includes_subposet(scope_set_name(xscope_type, name())));
  ensure(scope_set(xscope_type).has_id_space());

  // Exit:

  return;
}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

