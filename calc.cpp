#include "BackPanel.hpp"
#include "CalcFrame.hpp"

enum {
  ID_SCREEN = 10000,
  BUTTON_0 = 1000,
  BUTTON_1 = 1001,
  BUTTON_2 = 1002,
  BUTTON_3 = 1003,
  BUTTON_4 = 1004,
  BUTTON_5 = 1005,
  BUTTON_6 = 1006,
  BUTTON_7 = 1007,
  BUTTON_8 = 1008,
  BUTTON_9 = 1009,
  BUTTON_10 = 1010,  // add
  BUTTON_11 = 1011,  // sub
  BUTTON_12 = 1012,  // mul
  BUTTON_13 = 1013,  // dib
  BUTTON_14 = 1014,  // x^y
  BUTTON_15 = 1015,  // arrow up
  BUTTON_16 = 1016,  // swap
  BUTTON_17 = 1017,  // shgL
  BUTTON_18 = 1018,  // shgR
  BUTTON_19 = 1019,  // sign
  BUTTON_20 = 1020,  // vo
  BUTTON_21 = 1021,  // vp
  BUTTON_22 = 1022,  // sp
  BUTTON_23 = 1023,  // p
  BUTTON_24 = 1024,  // pp
  BUTTON_25 = 1025,  // cx
  BUTTON_26 = 1026,  // f
  BUTTON_27 = 1027,  // bp
  BUTTON_28 = 1028,  // pnt
};

BackPanel::BackPanel(wxFrame* parent, wxString calc, wxString buff,
                     wxBitmapType format)
    : wxPanel(parent) {
  calc_img.LoadFile(calc, format);
  buff_img.LoadFile(buff, format);
  Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(BackPanel::OnMouse));

  display = new wxTextCtrl(parent, ID_SCREEN, wxT(""), wxPoint(50, 20),
                           wxSize(500, 90), wxTE_RIGHT);
  display->SetFont(wxFontInfo(30));
  display->SetBackgroundColour(*wxBLACK);

  for (size_t i = 0; i < 8; i++) {
    registers[i] =
        new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(775, 780 - i * 40),
                       wxSize(162, 40), wxTE_RIGHT);
  }
  ring_buffer[0] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(990, 613),
                     wxSize(162, 45), wxTE_RIGHT);
  ring_buffer[1] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(1167, 613),
                     wxSize(162, 45), wxTE_RIGHT);
  ring_buffer[2] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(1350, 613),
                     wxSize(162, 45), wxTE_RIGHT);
  ring_buffer[5] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(1010, 768),
                     wxSize(162, 45), wxTE_RIGHT);
  ring_buffer[4] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(1190, 768),
                     wxSize(162, 45), wxTE_RIGHT);
  ring_buffer[3] =
      new wxTextCtrl(parent, ID_SCREEN, wxT("0"), wxPoint(1365, 768),
                     wxSize(162, 45), wxTE_RIGHT);
}

BackPanel::~BackPanel() {
  delete display;
  for (size_t i = 0; i < 8; i++) {
    delete registers[i];
  }
  for (size_t i = 0; i < 6; i++) {
    delete ring_buffer[i];
  }
}

wxTextCtrl* BackPanel::get_display() { return display; }

wxTextCtrl** BackPanel::get_regs() { return registers; }

wxTextCtrl** BackPanel::get_buff() { return ring_buffer; }

void BackPanel::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);
  setImage(dc);
}

void BackPanel::paintBack() {
  wxClientDC dc(this);
  setImage(dc);
}

void BackPanel::setImage(wxDC& dc) {
  dc.DrawBitmap(calc_img, 0, 0, false);
  dc.DrawBitmap(buff_img, 700, 500, false);
}

void BackPanel::OnMouse(wxMouseEvent& event){
    // wxString answ;
    // int x = event.GetX();
    // int y = event.GetY();
    // answ = answ.Format(wxT("(%d,  %d)"), x, y);
    // wxMessageBox(answ);
};

CalcFrame::CalcFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(1920, 1080)) {
  wxInitAllImageHandlers();

  sizer = new wxBoxSizer(wxHORIZONTAL);
  drawPanel = new BackPanel(this, wxT("Calc_pict/calcApp.png"),
                            wxT("Calc_pict/mem.png"), wxBITMAP_TYPE_PNG);

  mem = new Memory(drawPanel->get_display(), drawPanel->get_regs(),
                   drawPanel->get_buff());

  panel = new wxPanel(this, wxID_ANY);
  sizer->Add(drawPanel, 1, wxEXPAND, 10);

  btns = new wxImage[50];
  bitmap_btns = new wxBitmapButton[50];

  for (size_t i = 0; i < 10; i++) {
    new (btns + i) wxImage(wxT("Calc_pict/k" + std::to_string(i) + ".png"),
                           wxBITMAP_TYPE_PNG);
  }

  btns[10] = wxImage(wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG);
  btns[11] = wxImage(wxT("Calc_pict/minus.png"), wxBITMAP_TYPE_PNG);
  btns[12] = wxImage(wxT("Calc_pict/mult.png"), wxBITMAP_TYPE_PNG);
  btns[13] = wxImage(wxT("Calc_pict/delen.png"), wxBITMAP_TYPE_PNG);
  btns[14] = wxImage(wxT("Calc_pict/x^y.png"), wxBITMAP_TYPE_PNG);
  btns[15] = wxImage(wxT("Calc_pict/arowup.png"), wxBITMAP_TYPE_PNG);
  btns[16] = wxImage(wxT("Calc_pict/swap.png"), wxBITMAP_TYPE_PNG);
  btns[17] = wxImage(wxT("Calc_pict/shgL.png"), wxBITMAP_TYPE_PNG);
  btns[18] = wxImage(wxT("Calc_pict/shgR.png"), wxBITMAP_TYPE_PNG);
  btns[19] = wxImage(wxT("Calc_pict/sign.png"), wxBITMAP_TYPE_PNG);
  btns[20] = wxImage(wxT("Calc_pict/vo.png"), wxBITMAP_TYPE_PNG);
  btns[21] = wxImage(wxT("Calc_pict/vp.png"), wxBITMAP_TYPE_PNG);
  btns[22] = wxImage(wxT("Calc_pict/sp.png"), wxBITMAP_TYPE_PNG);
  btns[23] = wxImage(wxT("Calc_pict/p.png"), wxBITMAP_TYPE_PNG);
  btns[24] = wxImage(wxT("Calc_pict/pp.png"), wxBITMAP_TYPE_PNG);
  btns[25] = wxImage(wxT("Calc_pict/cx.png"), wxBITMAP_TYPE_PNG);
  btns[26] = wxImage(wxT("Calc_pict/f.png"), wxBITMAP_TYPE_PNG);
  btns[27] = wxImage(wxT("Calc_pict/bp.png"), wxBITMAP_TYPE_PNG);
  btns[28] = wxImage(wxT("Calc_pict/pnt.png"), wxBITMAP_TYPE_PNG);

  for (size_t i = 0; i < 29; i++) {
    btns[i].Scale(42, 42);
  }

  for (size_t i = 0; i < 10; i++) {
    if (i == 0) {
      new (bitmap_btns + i) wxBitmapButton(drawPanel, 1000 + i,
                                           wxBitmap(btns[i]), wxPoint(49, 772));
    } else {
      switch (i % 3) {
        case 0:
          new (bitmap_btns + i)
              wxBitmapButton(drawPanel, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(212, 415 + 112 * (3 - i / 3)));
          break;

        case 1:
          new (bitmap_btns + i)
              wxBitmapButton(drawPanel, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(49, 415 + 112 * (2 - i / 3)));
          break;

        case 2:
          new (bitmap_btns + i)
              wxBitmapButton(drawPanel, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(131, 415 + 112 * (2 - i / 3)));
          break;
      }
    }
  }

  {
    new (bitmap_btns + 10) wxBitmapButton(
        drawPanel, BUTTON_10, wxBitmap(btns[10]), wxPoint(424, 528));
    new (bitmap_btns + 11) wxBitmapButton(
        drawPanel, BUTTON_11, wxBitmap(btns[11]), wxPoint(424, 645));
    new (bitmap_btns + 12) wxBitmapButton(
        drawPanel, BUTTON_12, wxBitmap(btns[12]), wxPoint(334, 528));
    new (bitmap_btns + 13) wxBitmapButton(
        drawPanel, BUTTON_13, wxBitmap(btns[13]), wxPoint(334, 645));
    new (bitmap_btns + 14) wxBitmapButton(
        drawPanel, BUTTON_14, wxBitmap(btns[14]), wxPoint(240, 307));
    new (bitmap_btns + 15) wxBitmapButton(
        drawPanel, BUTTON_15, wxBitmap(btns[15]), wxPoint(424, 415));
    new (bitmap_btns + 16) wxBitmapButton(
        drawPanel, BUTTON_16, wxBitmap(btns[16]), wxPoint(320, 409));
    new (bitmap_btns + 17) wxBitmapButton(
        drawPanel, BUTTON_17, wxBitmap(btns[17]), wxPoint(162, 195));
    new (bitmap_btns + 18) wxBitmapButton(
        drawPanel, BUTTON_18, wxBitmap(btns[18]), wxPoint(245, 195));
    new (bitmap_btns + 19) wxBitmapButton(
        drawPanel, BUTTON_19, wxBitmap(btns[19]), wxPoint(248, 772));
    new (bitmap_btns + 20) wxBitmapButton(
        drawPanel, BUTTON_20, wxBitmap(btns[20]), wxPoint(332, 195));
    new (bitmap_btns + 21) wxBitmapButton(
        drawPanel, BUTTON_21, wxBitmap(btns[21]), wxPoint(354, 765));
    new (bitmap_btns + 22) wxBitmapButton(
        drawPanel, BUTTON_22, wxBitmap(btns[22]), wxPoint(419, 187));
    new (bitmap_btns + 23) wxBitmapButton(
        drawPanel, BUTTON_23, wxBitmap(btns[23]), wxPoint(160, 307));
    new (bitmap_btns + 24) wxBitmapButton(
        drawPanel, BUTTON_24, wxBitmap(btns[24]), wxPoint(412, 307));
    new (bitmap_btns + 25) wxBitmapButton(drawPanel, BUTTON_25,
                                          wxBitmap(btns[25]), wxPoint(40, 300));
    new (bitmap_btns + 26) wxBitmapButton(
        drawPanel, BUTTON_26, wxBitmap(btns[26]), wxPoint(469, 772));
    new (bitmap_btns + 27) wxBitmapButton(
        drawPanel, BUTTON_27, wxBitmap(btns[27]), wxPoint(330, 307));
    new (bitmap_btns + 28) wxBitmapButton(
        drawPanel, BUTTON_28, wxBitmap(btns[28]), wxPoint(154, 772));
  }

  for (size_t i = 0; i < 29; i++) {
    Connect(1000 + i, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(CalcFrame::press));
  }

  gs = new wxGridSizer(1, 1, 3, 3);

  sizerP = new wxBoxSizer(wxVERTICAL);
  sizerP->Add(gs, 1, 0);
  panel->SetSizer(sizerP);

  sizer->Add(panel, 0, wxLEFT, 60);
  SetSizer(sizer);
  Centre();
};

CalcFrame::~CalcFrame() {
  delete[] btns;
  delete[] bitmap_btns;
  delete mem;
  Close(true);
};

void CalcFrame::press(wxCommandEvent& event) {
  int id = event.GetId();
  mem->act(id - 1000);
}

class CalcApp : public wxApp {
  CalcFrame* frame;

 public:
  bool OnInit() {
    frame = new CalcFrame(wxT("БК-21"));
    frame->Show();
    SetTopWindow(frame);
    return true;
  }

  int OnExit() {
    // wxMessageBox(wxT("Все удалаяем"));

    return 0;
  }
};

IMPLEMENT_APP(CalcApp)