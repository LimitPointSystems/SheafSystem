
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class EQUIVALENCE

#include "assert_contract.h"

#ifndef EQUIVALENCE_H
#include "equivalence.h"
#endif

#ifdef PARALLEL_MPI

#ifndef POSET_H
#include "poset.h"
#endif

sheaf::equivalence::
equivalence(int xremote_index, int xremote_proc, poset_storage* xremote_storage)
{

  // preconditions:

  require(xremote_index >= 0);
  require(xremote_proc >= 0);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  require(xremote_proc < size);
  require(xremote_storage != 0);

  // body:

  _remote_index   = xremote_index;
  _remote_proc    = xremote_proc;
  _remote_storage = xremote_storage;

  // postconditions:

  ensure(remote_index()   == xremote_index);
  ensure(remote_proc()    == xremote_proc);
  ensure(remote_storage() == xremote_storage);

  ensure(invariant());
}

sheaf::equivalence::
~equivalence()
{}

bool
sheaf::equivalence::
invariant() const
{

  return true; /// $$HACK: placebo.  @todo develop a real invariant.
}

hid_t
sheaf::equivalence::
hdf_type()
{

  // body:

  static bool  first_call = true;
  static hid_t result     = -1;
  herr_t       rtncode    = -1;

  if (first_call)
  {

    first_call = false;

    /// @hack assumes MPI_Comm and MPI_Aint are MPI_INTs

    result = H5Tcreate(H5T_COMPOUND, sizeof(hdf_rep));
    assertion(result >= 0);
    rtncode = H5Tinsert(result,
                        "local_index",
                        HOFFSET(hdf_rep, local_index),
                        H5T_NATIVE_INT);
    assertion(rtncode >= 0);
    rtncode = H5Tinsert(result,
                        "remote_index",
                        HOFFSET(hdf_rep, remote_index),
                        H5T_NATIVE_INT);
    assertion(rtncode >= 0);
    rtncode = H5Tinsert(result,
                        "remote_proc",
                        HOFFSET(hdf_rep, remote_proc),
                        H5T_NATIVE_INT);
    assertion(rtncode >= 0);
  }

  // postconditions:

  ensure(result >= 0);

  /// @todo need something to ensure that the fields in the packet actually correspond
  /// to the class data fields.

  return result;
}

MPI_Datatype
sheaf::equivalence::
mpi_type()
{

  // body:

  static bool         first_call = true;
  static MPI_Datatype result     = MPI_DATATYPE_NULL;
  int                 rtncode    = MPI_SUCCESS;

  if (first_call)
  {

    first_call = false;

    /// @hack assumes MPI_Comm and MPI_Aint are MPI_INTs

    int          cts    = 3;
    MPI_Aint     displs = 0;
    MPI_Datatype types  = MPI_INT;

    rtncode = MPI_Type_struct(1,&cts,&displs,&types,&result);
    if (rtncode == MPI_SUCCESS)
      rtncode = MPI_Type_commit(&result);
  }

  // postconditions:

  ensure(rtncode == MPI_SUCCESS);
  ensure(result != MPI_DATATYPE_NULL);

  /// @todo need something to ensure that the fields in the packet actually correspond
  /// to the class data fields.

  return result;
}

void
sheaf::equivalence::
make_hdf_rep(hdf_rep* xhdf_rep, int xlocal_index)
{

  // preconditions:

  require(xhdf_rep != 0);
  require(xlocal_index >= 0);

  // body:

  xhdf_rep->local_index  =  xlocal_index;
  xhdf_rep->remote_index = _remote_index;
  xhdf_rep->remote_proc  = _remote_proc;
}

void
sheaf::equivalence::
make_mpi_rep(mpi_rep* xmpi_rep)
{

  // preconditions:

  require(xmpi_rep != 0);

  // body:

  xmpi_rep->remote_index   = _remote_index;
  xmpi_rep->remote_proc    = _remote_proc;
  assertion(MPI_Address(_remote_storage, &xmpi_rep->remote_storage) == MPI_SUCCESS);
}

/*
MPI_Comm
sheaf::equivalence::
communicator() {
 
  //  return _communicator;
}
*/

int
sheaf::equivalence::
remote_index()
{

  return _remote_index;
}

int
sheaf::equivalence::
remote_proc()
{

  return _remote_proc;
}

sheaf::poset_storage *
sheaf::equivalence::
remote_storage()
{

  return _remote_storage;
}


sheaf::equivalence::
equivalence(hdf_rep* xrep)
{

  // preconditions:

  require(xrep != 0);

  // body:

  _remote_index   = xrep->remote_index;
  _remote_proc    = xrep->remote_proc;
  _remote_storage = 0;

  // postconditions:

}

void
sheaf::equivalence::
put_remote_storage(poset_storage* xstorage)
{

  // preconditions:

  require(xstorage != 0);

  // body:

  _remote_storage = xstorage;

}

#endif // PARALLEL_MPI
