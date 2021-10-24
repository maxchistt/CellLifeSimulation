import { Component, Input } from '@angular/core';
import { IDrawEntity } from '../../interfaces/draw-interfaces';

@Component({
  selector: 'app-simulation-graphic',
  templateUrl: './simulation-graphic.component.html'
})
export class SimulationGraphicComponent {
  @Input() size: number[] = [0, 0];
  @Input()
  set frame(frame: IDrawEntity[]) { this._frame = frame; this.redraw(); }
  get frame(): IDrawEntity[] { return this._frame; }
  _frame: IDrawEntity[] = [];
  ctx: CanvasRenderingContext2D;

  redraw() {
    if (this.ctx) {
      this.ctx.clearRect(0, 0, this.ctx.canvas.width, this.ctx.canvas.height);
      this.frame.forEach((item: IDrawEntity) => this.drawCircle(item.y, item.x, item.size, item.color));
    }
  }

  drawCircle(x: number, y: number, size: number, color: string): void {
    this.ctx.strokeStyle = color;
    this.ctx.fillStyle = color;
    this.ctx.beginPath();
    this.ctx.arc(x, y, size / 2, 0, 2 * Math.PI, true);
    this.ctx.fill();
  }

}
