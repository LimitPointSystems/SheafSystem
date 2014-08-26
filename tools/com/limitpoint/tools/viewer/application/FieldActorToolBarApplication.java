
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

package com.limitpoint.tools.viewer.application;

import com.limitpoint.bindings.java.*;
import com.limitpoint.tools.viewer.render.*;

import java.awt.*;

/**
 * Interface for applications to embed a <code>FieldActorToolBar</code>
 */
public interface FieldActorToolBarApplication
{
  /**
   * Open up a 3d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG3DViewer(FieldActorDescriptor xactor);

  /**
   * Open up a 2d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG2DViewer(FieldActorDescriptor xactor);

  /**
   * Cancel the current <code>FieldActorToolBar</code>
   */
  public void cancelFieldActorToolBar();
}