import { Component, Input } from '@angular/core';
import { IDrawEntity } from '../../interfaces/draw-interfaces';

@Component({
  selector: 'app-datatable',
  templateUrl: './datatable.component.html',
  styleUrls: ['./datatable.component.css']
})
export class DatatableComponent {
  @Input() size: number[] = [0, 0];
  @Input()
  set frame(frame: IDrawEntity[]) { this._frame = frame; this.calccolors(); }
  get frame(): IDrawEntity[] { return this._frame; }
  _frame: IDrawEntity[] = [];

  colors: number[] = [0, 0, 0];

  calccolors = () => {
    this.colors = [0, 0, 0];
    this.frame.forEach(element => {
      if (element.color == "Red") {
        this.colors[0]++;
      } else if (element.color == "Green") {
        this.colors[1]++;
      } else if (element.color == "Blue") {
        this.colors[2]++;
      }
    });
  }

}
