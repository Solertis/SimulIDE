/***************************************************************************
 *   Copyright (C) 2016 by santiago González                               *
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

#include "mosfet.h"
#include "connector.h"
#include "itemlibrary.h"


Component* Mosfet::construct( QObject* parent, QString type, QString id )
{ return new Mosfet( parent, type, id ); }

LibraryItem* Mosfet::libraryItem()
{
    return new LibraryItem(
            tr( "Mosfet" ),
            tr( "Active" ),
            "mosfet.png",
            "Mosfet",
            Mosfet::construct);
}

Mosfet::Mosfet( QObject* parent, QString type, QString id )
    : Component( parent, type, id ), eMosfet( id.toStdString() )
{
    m_area =  QRectF( -12, -14, 28, 28 );
    
    QString newId = id;
    newId.append(QString("Gate"));
    Pin* newPin = new Pin( 180, QPoint(-16, 0), newId, 0, this );
    newPin->setLabelText( "" );
    newPin->setLabelColor( QColor( 0, 0, 0 ) );
    m_ePin[2] = newPin;
    newId.append(QString("-eSource"));
    m_gate = new eSource( newId.toStdString(), m_ePin[2] );
    m_gate->setImp( 1e5 );

    // D,S pins to eResistor m_ePin[0] m_ePin[1] 
    newId = id;
    newId.append(QString("Dren"));
    newPin = new Pin( 90, QPoint(8,-16), newId, 0, this );
    newPin->setLabelText( "" );
    newPin->setLabelColor( QColor( 0, 0, 0 ) );
    m_ePin[0] = newPin;
    
    newId = id;
    newId.append(QString("Sour"));
    newPin = new Pin( 270, QPoint(8, 16), newId, 1, this );
    newPin->setLabelText( "" );
    newPin->setLabelColor( QColor( 0, 0, 0 ) );
    m_ePin[1] = newPin;
}
Mosfet::~Mosfet(){}

void Mosfet::remove()
{
    if( m_ePin[0]->isConnected() ) (static_cast<Pin*>(m_ePin[0]))->connector()->remove();
    if( m_ePin[1]->isConnected() ) (static_cast<Pin*>(m_ePin[1]))->connector()->remove();
    if( m_ePin[2]->isConnected() ) (static_cast<Pin*>(m_ePin[2]))->connector()->remove();
    Component::remove();
}

void Mosfet::paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    Component::paint( p, option, widget );

    p->drawEllipse( m_area );
    
    p->setBrush( Qt::black );
    
    p->drawLine( -12, 0,-4, 0 );
    p->drawLine(  -4,-8,-4, 8 );
    
    p->drawLine( 0,-9, 0, -5 );
    p->drawLine( 0,-2, 0, 2 );
    p->drawLine( 0, 5, 0, 9 );
    
    p->drawLine( 0,-7.5, 8,-7.5 );
    p->drawLine( 0,   0, 8, 0 );
    p->drawLine( 0, 7.5, 8, 7.5 );
    
    p->drawLine( 8,-12, 8,-7.5 );
        p->drawLine( 8, 12, 8, 0 );

    if( m_Pchannel )
    {
         QPointF points[3] = {
         QPointF( 8, 0 ),
         QPointF( 3,-2 ),
         QPointF( 3, 2 ) };
         p->drawPolygon(points, 3);
    }
    else
    {
        QPointF points[3] = {
        QPointF( 1, 0 ),
        QPointF( 5,-2 ),
        QPointF( 5, 2 )     };
        p->drawPolygon(points, 3);
    }

   
}

#include "moc_mosfet.cpp"
