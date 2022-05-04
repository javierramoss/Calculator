#include <iostream>
#include <string>
#include <vector>
#include <elements.hpp>
#include "calculator.hpp"

using namespace cycfi::elements;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

auto render(view& view_, Calculator& calculator)
{
   static float const grid[] = { 1.0, 1.0 };

   auto in = input_box("0");
   in.second->on_text =
      [input = in.second.get()](std::string_view text) {};
   in.second->set_text("0");

   auto display =
      vtile(
         margin({0,20,0,20},
         top_margin(0, hgrid(grid, in.first))
         )
      );

   std::vector<layered_button> buttons;
   std::vector<std::string> icons = {
      "AC", "DEL", "(", ")",
      "^", "r", "x", "/",
      "7", "8", "9", "+",
      "4", "5", "6", "-",
      "1", "2", "3", ".",
      "0", "="
   };
   
   buttons.push_back(button(icons[0], 2));
   buttons[0].on_click = [&view_, &calculator, in, input = in.second.get()](bool) mutable {
         input->set_text("0");
         calculator.AC();
         calculator << input->get_text();
         calculator.evaluate();
         view_.refresh(*in.second);
      };
   
   buttons.push_back(button(icons[1], 2));
   buttons[1].on_click = [&view_, in, input = in.second.get()](bool) mutable {
         std::string temp = input->get_text();
         if (temp.size() == 1) {
             input->set_text("0");
         }
         else {
             input->set_text(temp.substr(0, temp.size() - 1));
         }
         view_.refresh(*in.second);
      };

   for (int i = 2; i < icons.size() - 1; i++) {
      buttons.push_back(button(icons[i], 2));
      buttons[i].on_click = [&view_, in, i, icons, input = in.second.get()](bool) mutable {
          if (input->get_text() == "0") {
              input->set_text(icons[i]);
          }
          else {
              input->set_text(input->get_text() + icons[i]);
          }
         view_.refresh(*in.second);
      };
   };

   buttons.push_back(button(icons[icons.size() - 1], 2));
   buttons[icons.size() - 1].on_click = [&view_, &calculator, in, input = in.second.get()](bool) mutable {
       calculator << input->get_text();
       calculator.evaluate();
       input->set_text(calculator.getAnswer());
       view_.refresh(*in.second);
   };

   auto button_grid =
      vtile(
         hgrid(buttons[0], buttons[1], buttons[2], buttons[3]),
         hgrid(buttons[4], buttons[5], buttons[6], buttons[7]),
         hgrid(buttons[8], buttons[9], buttons[10], buttons[11]),
         hgrid(buttons[12], buttons[13], buttons[14], buttons[15]),
         hgrid(buttons[16], buttons[17], buttons[18], buttons[19]),
         hgrid(buttons[20], buttons[21])
      );

   return
      fixed_size({ 400, 400 },
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

   Calculator calculator;

   view_.content(
      render(view_, calculator),
      background
   );

   _app.run();
   return 0;
}
