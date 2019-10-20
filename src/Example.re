module HomeScreen = {
  open ReactNative;
  [@react.component]
  let make = (~navigation, ~route) =>
    <Text> {j|Hello Reasonable Person!|j}->React.string </Text>;
};

module ModalScreen = {
  open ReactNative;
  [@react.component]
  let make = (~navigation, ~route) =>
    <Text> {j|Hello From Modal|j}->React.string </Text>;
};

module MainStackScreen = {
  open ReactNative;
  include Stack.Make({
    type params = {. "name": string};
  });
  [@react.component]
  let make = (~navigation, ~route) =>
    <Navigator>
      <Screen
        name="Home"
        component=HomeScreen.make
        options={props =>
          options(
            ~headerLeft=
              _ =>
                <Button
                  onPress={_ =>
                    props##navigation->Navigation.navigate("MyModal")
                  }
                  title="Info"
                  color="#fff"
                />,
            ~title=
              switch (props##route##params) {
              | Some(params) => params##name
              | None => "Reason"
              },
            (),
          )
        }
      />
    </Navigator>;
};

module RootStackScreen = {
  include Stack.Make({
    type params = unit;
  });
  let make = () =>
    <Native.NavigationNativeContainer>
      <Navigator mode=`modal headerMode=`none>
        <Screen name="Main" component=MainStackScreen.make />
        <Screen name="MyModal" component=ModalScreen.make />
      </Navigator>
    </Native.NavigationNativeContainer>;
};
