
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

package com.limitpoint.tools.viewer.table;

import com.limitpoimt.tools.viewer.render.*;
import com.limitpoint.bindings.java.*;

import java.awt.*;
import java.util.*;

/**
 *
 * Struct which describes an <code>FieldTable</code>
 *
 */
public class FieldTableDescriptor
{
  /**
   * The name of the <code>namespace_poset</code> for the field.
   */
  public String namespace = null;

  /**
   * The array of <code>SectionDescriptor</code>'s
   */
  public ArrayList<SectionDescriptor> sections =
    new ArrayList<SectionDescriptor>();

  /**
   * Default constructor
   */
  public FieldTableDescriptor()
  {}
}
