/*
Copyright 2022 The Foedag team

GPL License

Copyright (c) 2022 The Open-Source FPGA Foundation

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "AbstractReportManager.h"

namespace FOEDAG {

/* Placement-specific report manager. It triggers 'placement.rpt' log file
 * parsing and creates two reports:
 * - Report Resource Utilization, shown as table in application editor area;
 * - Report Static Timing, placed into post_place_timing.rpt file.
 */
class PlacementReportManager final : public AbstractReportManager {
 public:
  PlacementReportManager(const TaskManager &taskManager);

 private:
  QStringList getAvailableReportIds() const override;
  std::unique_ptr<ITaskReport> createReport(const QString &reportId) override;
  QString getTimingLogFileName() const override;
  bool isStatisticalTimingLine(const QString &line) override;
  bool isStatisticalTimingHistogram(const QString &line) override;
  void splitTimingData(const QString &timingStr) override;
  void parseLogFile() override;

  SectionKeys m_createDeviceKeys;
  SectionKeys m_placementKeys;

  IDataReport::ColumnValues m_circuitColumns;
  IDataReport::ColumnValues m_bramColumns;
  IDataReport::ColumnValues m_dspColumns;
  IDataReport::TableData m_circuitData;
  IDataReport::TableData m_bramData;
  IDataReport::TableData m_dspData;
};

}  // namespace FOEDAG
