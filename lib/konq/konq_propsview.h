/*  This file is part of the KDE project
    Copyright (C) 1997 David Faure <faure@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __konq_viewprops_h__
#define __konq_viewprops_h__

#include <qpixmap.h>

#include <kurl.h>

class KInstance;
class KConfigBase;
class KConfig;

/**
 * The class KonqPropsView holds the properties for a Konqueror View
 *
 * Separating them from the view class allows to store the default
 * values (the one read from <kinstance>rc) in one instance of this class
 * and to have another instance of this class in each view, storing the
 * current values of the view.
 *
 * The local values can be read from a desktop entry, if any (.directory,
 * bookmark, ...). [ .directory is implemented, bookmark isn't ].
 */
class KonqPropsView
{
public:

  /**
   * Constructs a KonqPropsView instance from an instance config file.
   * defaultProps is a "parent" object. If non null, then this instance
   * is the one used by a view, and its value can differ from the default ones.
   * The instance parameter should be the same for both...
   */
  KonqPropsView( KInstance * instance, KonqPropsView * defaultProps /*= 0L*/ );

  /** Destructor */
  virtual ~KonqPropsView();

  /**
   * Is this the instance representing default properties ?
   */
  bool isDefaultProperties() {
      // No parent -> we are the default properties
      return m_defaultProps == 0L;
  }

  /**
   * Called when entering a directory
   * Checks for a .directory, read it.
   * Don't do this on the default properties instance
   * Returns TRUE if the settings for the new directories are
   * different from the settings in the old directory.
   */
  bool enterDir( const KURL & dir );

  /**
   * Turn on/off saving properties locally
   * Don't do this on the default properties instance
   */
  void setSaveViewPropertiesLocally( bool value );

  ///

  void setIconSize( int size ); // in pixel, 0 for default
  int iconSize() { return m_iIconSize; }

  void setItemTextPos( int pos ); // QIconView::Bottom or QIconView::Right, currently
  int itemTextPos() { return m_iItemTextPos; }

  void setShowingDotFiles( bool show );
  bool isShowingDotFiles() const { return m_bShowDot; }

  void setShowingImagePreview( bool show );
  bool isShowingImagePreview() const { return m_bImagePreview; }

  void setBgColor( const QColor & color );
  const QColor& bgColor() const { return m_bgColor; }
  void setBgPixmapFile( const QString & file );
  const QString& bgPixmapFile() const { return m_bgPixmapFile; }
  const QPixmap& bgPixmap() const { return m_bgPixmap; } // A helper for the above

  // TODO : window size - hmm, that applies only if there is only ONE view...
  // .. and if we open that dir in a new window...

protected:

  void loadPixmap();

  // The actual properties

  int m_iIconSize;
  int m_iItemTextPos;
  bool m_bShowDot;
  bool m_bImagePreview;
  QColor m_bgColor;
  QString m_bgPixmapFile;
  QPixmap m_bgPixmap;

  // Path to .directory file, whether it exists or not
  QString dotDirectory;

  // Current config object for _saving_
  KConfigBase * currentConfig();

  QString currentGroup() {
      return isDefaultProperties() ? "Settings" : "URL properties";
  }

  bool m_bSaveViewPropertiesLocally;

  // True if we found a .directory file to read
  bool m_dotDirExists;

  // Points to the current .directory file if we are in
  // save-view-properties-locally mode, otherwise to the global config
  // It is set to 0L to mark it as "needs to be constructed".
  // This is to be used for SAVING only.
  // Can be a KConfig or a KSimpleConfig
  KConfigBase * m_currentConfig;

  // If this is not a "default properties" instance (but one used by a view)
  // then m_defaultProps points to the "default properties" instance
  // Otherwise it's 0L.
  KonqPropsView * m_defaultProps;

private:
  KonqPropsView( const KonqPropsView & );
  KonqPropsView();
};


#endif
