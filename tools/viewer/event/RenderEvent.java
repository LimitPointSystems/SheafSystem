
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

import java.awt.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * rendering a scene.
 *
 */
public class RenderEvent extends RenderThreadEvent
{
  /**
   * The <code>SceneDescriptor</code>
   */
  protected SceneDescriptor scene;

  /**
   * The reset view flag
   */
  protected boolean resetView;

  /**
   * The record mode
   */
  protected boolean recordMode;

  /**
   * The constructor
   */
  public RenderEvent(SceneDescriptor xscene,
                     boolean xresetView,
                     boolean xrecordMode)
  {
    scene = xscene;
    resetView = xresetView;
    recordMode = xrecordMode;
  }

  /**
   * Handle this <code>RenderEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    setScreenCursor(xrenderThread, Cursor.WAIT_CURSOR);

    xrenderThread.copy(scene);

    if(abort)
    {
      setScreenCursor(xrenderThread, Cursor.DEFAULT_CURSOR);
      return;
    }

    xrenderThread.update();

    if(abort)
    {
      setScreenCursor(xrenderThread, Cursor.DEFAULT_CURSOR);
      return;
    }

    if(resetView)
      xrenderThread.resetView();

    if(abort)
    {
      setScreenCursor(xrenderThread, Cursor.DEFAULT_CURSOR);
      return;
    }

    if(recordMode)
      xrenderThread.record(scene.scene);
    else
      xrenderThread.render();

    setScreenCursor(xrenderThread, Cursor.DEFAULT_CURSOR);
  }
}
