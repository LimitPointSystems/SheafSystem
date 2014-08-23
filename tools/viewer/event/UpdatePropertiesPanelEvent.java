
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
package com.limitpoint.tools.viewer.event;

import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.user.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * saving the render window to an image.
 *
 */
public class UpdatePropertiesPanelEvent extends RenderThreadEvent
{
  /**
   * The properties panel
   */
  protected PropertiesPanel panel;

  /**
   * The constructor
   */
  public UpdatePropertiesPanelEvent(PropertiesPanel xpanel)
  {
    panel = xpanel;
  }

  /**
   * Handle this <code>UpdatePropertiesPanelEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    panel.initValues();
    panel.setWaitState(false);
  }
}
