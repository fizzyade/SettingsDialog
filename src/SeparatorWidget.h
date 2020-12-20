/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of Pingnoo (https://github.com/fizzyade/pingnoo)
 *
 * An open-source cross-platform traceroute analyser.
 *
 * Created by Adrian Carpenter on 20/12/2020.
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
 */
#ifndef NEDRYSOFT_SEPARATORWIDGET_H
#define NEDRYSOFT_SEPARATORWIDGET_H

#include <QWidget>

namespace Nedrysoft::SettingsDialog {
    /**
     * @brief       The SeparatorWidget class draws a separating line.
     */
    class SeparatorWidget :
            public QWidget {

        private:
            Q_OBJECT

        protected:
            /**
             * @brief       Reimplements QWidget::paintEvent(QPainEvent *event)
             *
             * @param[in]   event the event.
             */
            void paintEvent(QPaintEvent *event) override;
    };
}



#endif //NEDRYSOFT_SEPARATORWIDGET_H
