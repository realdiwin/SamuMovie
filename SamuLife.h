#ifndef SamuLife_H
#define SamuLife_H

/**
 * @brief Samu has learnt the rules of Conway's Game of Life
 *
 * @file GameOfLife.h
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.1
 *
 * @section LICENSE
 *
 * Copyright (C) 2015, 2016 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * Samu (Nahshon) has learnt the rules of Conway's Game of Life. This is 
 * an example of the paper entitled "Samu in his prenatal development".
 */

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QFont>
#include <QCloseEvent>
#include "Converter.h"
#include "GameOfLife.h"

class SamuLife : public QMainWindow
{
    Q_OBJECT

    int movieCapWidth {4}, movieCapHeight {4};
    GameOfLife *gameOfLife;
    bool **lattice {nullptr};
    bool **prediction {nullptr};

    Converter *_converter;
    void closeEvent(QCloseEvent *evt);


public slots :
    void updateCells ( bool **, bool ** );

public:
    SamuLife ( int w = 30, int h = 20, QWidget *parent = 0 );
    virtual ~SamuLife();
    void paintEvent ( QPaintEvent* );
    void keyPressEvent( QKeyEvent * event );


};

#endif // SamuLife_H
