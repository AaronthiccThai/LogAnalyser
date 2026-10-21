#ifndef REPORT_FORMATTER_H
#define REPORT_FORMATTER_H

#include <iostream>
#include <string>

namespace ReportFormatter {

  constexpr int REPORT_WIDTH = 60;

  inline void printHeader(std::ostream& out, const std::string& title) {
    out << "\n" << std::string(REPORT_WIDTH, '=') << "\n";
    out << "  " << title << "\n";
    out << std::string(REPORT_WIDTH, '=') << "\n\n";
  }

  inline void printSection(std::ostream& out, const std::string& title) {
    out << "\n" << title << "\n";
    out << std::string(REPORT_WIDTH, '-') << "\n";
  }

}

#endif