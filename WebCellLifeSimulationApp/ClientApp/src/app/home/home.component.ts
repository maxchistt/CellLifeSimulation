import { Component } from '@angular/core';
import { IDrawEntity } from '../interfaces/draw-interfaces';
import { DataService } from '../services/data.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent {
  frame: IDrawEntity[] = [];
  size: number[] = [2, 2];

  connections: number = 0;
  collapse: boolean = false;

  constructor(protected base: DataService) {
    base.setUpdateCallback(this.updateHandler);
    base.getSize().then(this.setSize);
    base.initWebSocket().then(this.connectedHandler);
  }

  updateHandler = (frame: IDrawEntity[]): void => { this.frame = frame; };
  connectedHandler = (connections: number): void => { this.connections = connections; };
  setSize = (result: number[]) => this.size = result;
}