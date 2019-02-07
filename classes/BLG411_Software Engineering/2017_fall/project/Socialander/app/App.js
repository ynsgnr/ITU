
import React, { Component } from 'react'

import {
  AppRegistry,
  StyleSheet,
  Text,
  View
} from 'react-native'

import {
  Schema,
  Scene,
  Router,
  Route,
  Actions,
  Reducer,
  ActionConst,
  Lightbox,
} from 'react-native-router-flux'

import { Provider } from 'react-redux'

const store = configureStore();

export default class App extends Component {

      render(){
        return (
          <Provider store={store}>
            <Router>

            </Router>
          </Provider>
        );
      }
}
