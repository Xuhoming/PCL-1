/*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2010, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
*
*/
#ifndef PCL_MODELER_PARAMETER_H_
#define PCL_MODELER_PARAMETER_H_

#include <map>
#include <string>

#include <boost/any.hpp>

#include <QModelIndex>

class QWidget;
class QAbstractItemModel;

namespace pcl
{
  namespace modeler
  {
    class Parameter
    {
      public:
        Parameter(const std::string& name, const std::string& description, const boost::any& value):
          name_(name), description_(description), default_value_(value), current_value_(value){}
        ~Parameter(void) {}

        const std::string&
        getName() const {return name_;}

        const std::string&
        getDescription()const {return description_;}

        void
        reset() {current_value_ = default_value_;}

        virtual std::string
        valueTip() = 0;

        virtual QWidget*
        createEditor(QWidget *parent) = 0;

        virtual void
        setEditorData(QWidget *editor) = 0;

        virtual void
        setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) = 0;

        virtual QString
        toString() = 0;

        virtual void
        loadValue(const std::string& valueString) = 0;

      protected:
        std::string     name_;
        std::string     description_;
        boost::any      default_value_;
        boost::any      current_value_;
    };

    class IntParameter : public Parameter
    {
      public:
        IntParameter(const std::string& name, const std::string& description, int value, int low, int high, int step=1):
          Parameter(name, description, value), low_(low), high_(high), step_(step){}
        ~IntParameter(){}

        operator int() const {return boost::any_cast<int>(current_value_);}

        virtual std::string
        valueTip();

        virtual QWidget*
        createEditor(QWidget *parent);

        virtual void
        setEditorData(QWidget *editor);

        virtual void
        setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);

        virtual QString
        toString();

        virtual void
        loadValue(const std::string& valueString);
      protected:
        int     low_;
        int     high_;
        int     step_;
    };

    template <class T>
    class EnumParameter : public Parameter
    {
      public:
        EnumParameter(const std::string& name, const std::string& description, T value, const std::map<T, std::string>& candidates):
          Parameter(name, description, value), candidates_(candidates){}
        ~EnumParameter(){}

        operator T() const {return boost::any_cast<T>(current_value_);}

        virtual std::string
        valueTip();

        virtual QWidget*
        createEditor(QWidget *parent);

        virtual void
        setEditorData(QWidget *editor);

        virtual void
        setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);

        virtual QString
        toString();

        virtual void
        loadValue(const std::string& valueString);

      protected:
        const std::map<T, std::string> candidates_;
    };

    class DoubleParameter : public Parameter
    {
      public:
        DoubleParameter(const std::string& name, const std::string& description, double value, double low, double high, double step=0.01):
          Parameter(name, description, value), low_(low), high_(high), step_(step){}
        ~DoubleParameter(){}

        operator double() const {return boost::any_cast<double>(current_value_);}

        virtual std::string
        valueTip();

        virtual QWidget*
        createEditor(QWidget *parent);

        virtual void
        setEditorData(QWidget *editor);

        virtual void
        setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);

        virtual QString
        toString();

        virtual void
        loadValue(const std::string& valueString);

      protected:
        double  low_;
        double  high_;
        double  step_;
    };

  }
}

#endif // PCL_MODELER_PARAMETER_H_
