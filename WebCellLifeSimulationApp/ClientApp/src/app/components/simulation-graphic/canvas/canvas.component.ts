import { Component, ViewChild, ElementRef, AfterViewInit, Output, Input, EventEmitter } from '@angular/core';
import { element } from 'protractor';
import { IDrawEntity } from '../../../interfaces/draw-interfaces';

@Component({
  selector: 'app-canvas',
  templateUrl: './canvas.component.html'
})
export class CanvasComponent implements AfterViewInit {
  @ViewChild('innerCanvas', { static: false }) innerCanvas: ElementRef;
  @Input() canvasContext: CanvasRenderingContext2D;
  @Output() canvasContextChange = new EventEmitter<CanvasRenderingContext2D>();
  @Input()
  set size(size: number[]) { this._size = size; this.resize(); }
  get size(): number[] { return this._size; }
  _size: number[] = [100, 100];

  getThisCtx = (): CanvasRenderingContext2D => this.innerCanvas.nativeElement.getContext('2d');

  resize = () => {
    if (this.canvasContext) {
      this.canvasContext.canvas.height = this.size[0];
      this.canvasContext.canvas.width = this.size[1];
    }
  }

  constructor() { };

  ngAfterViewInit(): void {
    this.canvasContext = this.getThisCtx();
    this.canvasContextChange.emit(this.getThisCtx());
    this.resize();
  }

}
