import { Component, ViewChild, ElementRef, AfterViewInit, Output, Input, EventEmitter } from '@angular/core';
import { element } from 'protractor';
import { IDrawEntity } from '../../../interfaces/draw-interfaces';

@Component({
  selector: 'app-canvas',
  templateUrl: './canvas.component.html'
})
export class CanvasComponent implements AfterViewInit {
  @ViewChild('innerCanvas', { static: false }) innerCanvas: ElementRef;
  @Output() canvasContextChange = new EventEmitter<CanvasRenderingContext2D>();
  get canvasContext(): CanvasRenderingContext2D {
    return this._canvasContext;
  }
  private _canvasContext: CanvasRenderingContext2D;
  @Input()
  set size(size: number[]) { this._size = size; this.resize(); }
  get size(): number[] { return this._size; }
  private _size: number[] = [100, 100];

  resize = () => {
    if (this.canvasContext) {
      this.canvasContext.canvas.height = this.size[0];
      this.canvasContext.canvas.width = this.size[1];
    }
  }

  ngAfterViewInit(): void {
    this._canvasContext = this.innerCanvas.nativeElement.getContext('2d');
    this.canvasContextChange.emit(this.canvasContext);
    this.resize();
  }
}
