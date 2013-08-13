
/**
 * Classname: ProxyListener
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:54 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.event;

import java.util.EventListener;

/**
 *
 *
 */
public interface ProxyListener extends EventListener
{
  /**
    * Called whenever the <code>Proxy</code> changes.
    * @param event the event that characterizes the change.
    */
  void valueChanged(ProxyEvent event);
}

