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

#include "resistor.h"
#include "connector.h"
#include "itemlibrary.h"


Component* Resistor::construct( QObject* parent, QString type, QString id )
{ return new Resistor( parent, type, id ); }

LibraryItem* Resistor::libraryItem()
{
    return new LibraryItem(
            tr( "Resistor" ),
            tr( "Passive" ),
            "resistor.png",
            "Resistor",
            Resistor::construct);
}

Resistor::Resistor( QObject* parent, QString type, QString id )
    : Component( parent, type, id ),
      eResistor( id.toStdString() )
{
    QString pinId = m_id;
    pinId.append(QString("-lPin"));
    QPoint pinPos = QPoint(-8-8,0);
    m_ePin[0] = new Pin( 180, pinPos, pinId, 0, this);

    pinId = m_id;
    pinId.append(QString("-rPin"));
    pinPos = QPoint(8+8,0);
    m_ePin[1] = new Pin( 0, pinPos, pinId, 1, this);

    //m_idLabel->setText( QString("") );
    m_idLabel->setPos(-12,-24);
    setLabelPos(-12,-24, 0);
    
    m_unit = "Ω";
    setResist( m_resist );
    setValLabelPos(-16, 6, 0);
    //m_valLabel->setPos(-16, 6);
    setShowVal( true );
}
Resistor::~Resistor(){}

double Resistor::resist() { return m_value; }

void Resistor::setResist( double r )
{
    Component::setValue( r );       // Takes care about units multiplier
    eResistor::setResSafe( m_value*m_unitMult );
}

void Resistor::setUnit( QString un ) 
{
    Component::setUnit( un );
    eResistor::setResSafe( m_value*m_unitMult );
}

void Resistor::remove()
{
    if( m_ePin[0]->isConnected() ) (static_cast<Pin*>(m_ePin[0]))->connector()->remove();
    if( m_ePin[1]->isConnected() ) (static_cast<Pin*>(m_ePin[1]))->connector()->remove();
    Component::remove();
}

void Resistor::paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    Component::paint( p, option, widget );

    p->drawRect( -10.5, -4, 21, 8 );
}

#include "moc_resistor.cpp"
