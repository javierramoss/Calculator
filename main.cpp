#include <iostream>
#include <vector>
#include <elements.hpp>

using namespace cycfi::elements;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

auto render(view& view_)
{
   static float const grid[] = { 0.32, 1.0 };

   auto in = input_box("0");
   in.second->on_text =
      [input = in.second.get()](std::string_view text) {};

   auto display =
      vtile(
         margin({0,20,0,20},
         top_margin(0, hgrid(grid, in.first))
         )
      );

   std::vector<layered_button> buttons;
   std::vector<std::string> icons = {
      "AC", "DEL", "^", "s",
      "7", "8", "9", "x",
      "4", "5", "6", "/",
      "1", "2", "3", "+",
      "0", ".", "=", "-"
   };

   for (int i = 0; i < icons.size(); i++) {
      buttons.push_back(button(icons[i]));
      buttons[i].on_click = [&view_, in, i, icons, input = in.second.get()](bool) mutable {
         input->set_text(icons[i]);
         view_.refresh(*in.second);
      };
   };

   auto button_grid =
      vtile(
         hgrid(buttons[0], buttons[1], buttons[2], buttons[3]),
         hgrid(buttons[4], buttons[5], buttons[6], buttons[7]),
         hgrid(buttons[8], buttons[9], buttons[10], buttons[11]),
         hgrid(buttons[12], buttons[13], buttons[14], buttons[15]),
         hgrid(buttons[16], buttons[17], buttons[18], buttons[19])
      );

   return
      max_size({ 1280, 640 },
         margin(
            { 10, 10, 10, 10 },
            vtile(
               display,
               button_grid,
               empty()
            )
         )
      );
}

int main(int argc, char* argv[])
{
   app _app(argc, argv, "Calculator", "");
   window _win(_app.name());
   _win.on_close = [&_app]() { _app.stop(); };

   view view_(_win);

   view_.content(
      render(view_),
      background
   );

   _app.run();
   return 0;
}
