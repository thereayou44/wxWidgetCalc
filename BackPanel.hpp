#include <wx/defs.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class BackPanel : public wxPanel {
  wxBitmap calc_img;
  wxBitmap buff_img;
  wxTextCtrl* display;

  wxTextCtrl* registers[8];
  wxTextCtrl* ring_buffer[6];

 public:
  BackPanel(wxFrame*, wxString, wxString, wxBitmapType);
  ~BackPanel();
  void paintEvent(wxPaintEvent&);
  void paintBack();

  wxTextCtrl* get_display();
  wxTextCtrl** get_regs();
  wxTextCtrl** get_buff();

  void setImage(wxDC&);
  void OnMouse(wxMouseEvent&);
};