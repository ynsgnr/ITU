import React, { Component } from 'react';
import {
  AppRegistry
} from 'react-native';

import FCM, { FCMEvent, NotificationType } from 'react-native-fcm';

import App from './app/App.js';

export default class Burda extends Component {
    render() {
        return (
            <App />
        );
    }
}

AppRegistry.registerComponent('Burda', () => Burda);
