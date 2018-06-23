//
//  CSAlignView.cpp
//  CppStep
//
//  Copyright � 2018 Jonathan Tanner. All rights reserved.
//
//This file is part of CppStep.
//
//CppStep is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//CppStep is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with CppStep.  If not, see <http://www.gnu.org/licenses/>.

#include "CSAlignView.hpp"
#include <iostream>

CSAlignView::CSAlignView(CSRect rect, Direction dir) : superView(new CSSuperView(rect)), dir(dir) {}

void CSAlignView::addView(CSView* subView, bool expanding) {
    subViews.push_back(std::make_pair(subView, expanding));
    superView->addView(subView);
    relayout();
}

void CSAlignView::relayout() {
    int noExpanding = std::count_if(subViews.begin(),
                                    subViews.end(),
                                    [](std::pair<CSView*, bool> subView) {
                                        return subView.second;
                                    });
    fixedLength = std::accumulate(subViews.begin(),
                                  subViews.end(),
                                  0.0,
                                  [this](double x, std::pair<CSView*, bool> subView) {
                                      if (subView.second) {
                                          return x;
                                      } else {
                                          switch (this->dir) {
                                              case Direction::Horizontal:
                                                  return x + subView.first->getWidth();
                                                  break;
                                              case Direction::Vertical:
                                                  return x + subView.first->getHeight();
                                                  break;
                                              default:
                                                  //Shouldn't happen
                                                  return x;
                                                  break;
                                          }
                                      }
                                  });
    double fullLength;
    switch (dir) {
        case Direction::Horizontal:
            fullLength = getWidth();
            break;
        case Direction::Vertical:
            fullLength = getHeight();
            break;
    }
    double expandedLength = (fullLength - fixedLength) / noExpanding;
    double length = 0;
    for (std::pair<CSView*, bool> subView : subViews) {
        CSView* view = subView.first;
        bool expanded = subView.second;
        switch (dir) {
            case Direction::Horizontal:
                if (expanded) {
                    view->setWidth(expandedLength);
                }
                view->setHeight(getHeight());
                view->setX(length);
                view->setY((getHeight() - view->getHeight()) / 2);
                length += view->getWidth();
                break;
            case Direction::Vertical:
                if (expanded) {
                    view->setHeight(expandedLength);
                }
                view->setWidth(getWidth());
                view->setY(length);
                view->setX((getWidth() - view->getWidth()) / 2);
                length += view->getHeight();
                break;
        }
    }
}

CSView::NativeView CSAlignView::toNativeView() {
    return superView->toNativeView();
}
