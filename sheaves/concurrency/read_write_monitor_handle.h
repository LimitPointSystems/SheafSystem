
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Interface for class read_write_monitor_handle

#ifndef READ_WRITE_MONITOR_HANDLE_H
#define READ_WRITE_MONITOR_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

// class read_write_monitor;

#ifndef READ_WRITE_MONITOR_H
#include "read_write_monitor.h"
#endif

namespace sheaf
{
  
///
/// A handle for a hidden read_write_monitor state.
///
class SHEAF_DLL_SPEC read_write_monitor_handle : public any
{

public:

  ///
  /// True if other conforms to current
  ///
  virtual bool is_ancestor_of(const any* xother) const;


  ///
  /// Make a new, unattached handle of the same type as this.
  ///
  virtual read_write_monitor_handle* clone() const;

  ///
  /// Descturctor.
  ///
  virtual ~read_write_monitor_handle();

  // ===========================================================
  /// @name GLOBAL ACCESS CONTROL FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if access control mechanism is disabled.
  /// Default value is enabled (false) and access is controlled
  /// by the per-thread access control functions.
  /// Disabled (true) is equivalent to having read-write access
  /// at all times, irrespective of any access control requests.
  /// Synonym for read_write_monitor::access_control_disabled().
  ///
  static bool access_control_disabled();

  //   ///
  //   /// Disables access control.
  //   /// Disabled (true) is equivalent to having read-write access
  //   /// at all times, irrespective of any access control requests.
  //   /// Synonym for read_write_monitor::disable_access_control().
  //   /// Should only be invoked once at beginning of a program, before any
  //   /// other SheafSystem calls. Once disabled, access control can not be re-enabled.
  //   ///
  //   static void disable_access_control();

  ///
  /// Enables access control.
  /// Synonym for read_write_monitor::enable_access_control().
  /// Should only be invoked once at beginning of a program, before any
  /// other SheafSystem calls. Once enabled, access control can not be disabled.
  ///
  static void enable_access_control();

protected:

private:

  //@}

public:

  // ===========================================================
  // PER-THREAD STATE ACCESS CONTROL FACET
  // ===========================================================

  ///
  /// True if this handle has a state associated with it.
  ///
  virtual bool is_attached() const;

  ///
  /// True if this is attached and the state is 
  /// accessible for read access but not for write.
  ///
  bool state_is_read_only_accessible() const;

  ///
  /// True if this is attached and the state is 
  /// not accessible for read only access.
  ///
  bool state_is_not_read_only_accessible() const;

  ///
  /// True if this is attached and if the state is accessible 
  /// for read or access control is disabled.
  ///
  bool state_is_read_accessible() const;

  ///
  /// True if this is attached and if the state is accessible 
  /// for read or if access control is disabled.
  ///
  bool state_is_not_read_accessible() const;

  ///
  /// True if the state is auto accessible for read,
  /// that is, if the state is already accessible for read
  /// or if this is attached and xuto_access is true.
  ///
  bool state_is_auto_read_accessible(bool xauto_access) const;

  ///
  /// True if this is attached and if the state is accessible for 
  /// read and write or access control is disabled.
  ///
  bool state_is_read_write_accessible() const;

  ///
  /// True if state is attached and if not accessible for 
  /// read and write or access control is disabled.
  ///
  bool state_is_not_read_write_accessible() const;

  ///
  /// True if state is auto accessible for read and write,
  /// that is, if the state is already accessible for read and write
  /// or if this is attached and xuto_access is true.
  /// or if this is attached and access control is disabled.
  ///
  bool state_is_auto_read_write_accessible(bool xauto_access) const;

  ///
  /// The number of times access has been requested
  /// and granted without being released.
  ///
  int access_request_depth() const;

  ///
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

  // ===========================================================
  // MODE LOCK CONTROL FACET
  // ===========================================================

  ///
  /// Obsolete.
  ///
  bool state_is_mode_locked() const;

  ///
  /// Obsolete.
  ///
  int mode_lock_ct() const;

  ///
  /// Obsolete.
  ///
  void get_mode_lock() const;

  ///
  /// Obsolete.
  ///
  void release_mode_lock();

  // ===========================================================
  // NOTIFICATION FACET
  // ===========================================================

  ///
  /// True if write access has been granted and released
  /// since the last call to clear_state_is_modified().
  ///
  bool state_is_modified() const;

  ///
  /// Sets the state_is_modified floag to false.
  ///
  void clear_state_is_modified();

protected:

  ///
  /// State object for this handle.
  ///
  virtual read_write_monitor* state_obj() const = 0;

  ///
  /// True if thread of control is still in constructor.
  ///
  inline bool access_guards_disabled() const
  {
    return state_obj()->access_guards_disabled();
  };

  ///
  /// Disables access guards; intended for use only within constructors of
  /// monitored objects, where no other client can possibly have access (yet).
  ///
  inline void disable_access_guards()
  {
    state_obj()->disable_access_guards();
  };

  ///
  /// Re-enables access guards.
  ///
  inline void enable_access_guards()
  {
    state_obj()->enable_access_guards();
  };
};

} // namespace sheaf

#endif // ifndef READ_WRITE_MONITOR_HANDLE_H
