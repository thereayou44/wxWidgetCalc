#include <wx/defs.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include "memory.hpp"

class CalcFrame : public wxFrame {
  wxBoxSizer *sizer, *sizerP;

  BackPanel* buffer;
  BackPanel* drawPanel;
  wxPanel* panel;

  wxBitmapButton* bitmap_btns;
  wxTextCtrl* number_scr;
  wxGridSizer* gs;

  wxImage* btns;

  Memory* mem;

 public:
  wxTextCtrl* display;
  CalcFrame(const wxString& title);
  ~CalcFrame();
  void Upd();
  void press(wxCommandEvent& event);
};