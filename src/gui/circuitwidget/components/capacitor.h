/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "e-capacitor.h"

#include "pin.h"

class LibraryItem;

class MAINMODULE_EXPORT Capacitor : public Component, public eCapacitor
{
    Q_OBJECT
    Q_PROPERTY( double Capacitance   READ capac    WRITE setCapac   DESIGNABLE true USER true )
    Q_PROPERTY( QString  Unit        READ unit     WRITE setUnit    DESIGNABLE true USER true )
    Q_PROPERTY( bool     Show_Cap    READ showVal  WRITE setShowVal DESIGNABLE true USER true )
    
    public:

        Capacitor( QObject* parent, QString type, QString id );
        ~Capacitor();

        static Component* construct( QObject* parent, QString type, QString id );
        static LibraryItem* libraryItem();
        
        double capac();
        void  setCapac( double c );
        
        void setUnit( QString un );

        virtual void paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget );

    public slots:

    private:
};

#endif

