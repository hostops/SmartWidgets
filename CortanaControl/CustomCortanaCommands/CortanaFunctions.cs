using System;
using System.Collections.Generic;
using Windows.UI.Popups;
using System.Diagnostics;

using Windows.Storage;
using Windows.ApplicationModel;
using Windows.ApplicationModel.VoiceCommands;

using Windows.System;
using Windows.Media.SpeechRecognition;
using Windows.ApplicationModel.Activation;
using uPLibrary.Networking.M2Mqtt;
using System.Text;

namespace CustomCortanaCommands
{

    class CortanaFunctions
    {
        public static MqttClient client;
        /*
        This is the lookup of VCD CommandNames as defined in 
        CustomVoiceCommandDefinitios.xml to their corresponding actions
        */
        private readonly static IReadOnlyDictionary<string, Delegate> vcdLookup = new Dictionary<string, Delegate>{

            /*
            {<command name from VCD>, (Action)(async () => {
                 <code that runs when that commmand is called>
            })}
            */

            {"LightTurnOn", (Action)(() => {
                client = new MqttClient("192.168.2.200");
                client.Connect(Guid.NewGuid().ToString());
                client.Publish("gTurn/sobaHostnik/mainLight", Encoding.UTF8.GetBytes("ON"));
             })},

            {"LightTurnOff", (Action)(() => {
                client = new MqttClient("192.168.2.200");
                client.Connect(Guid.NewGuid().ToString());
                client.Publish("gTurn/sobaHostnik/mainLight", Encoding.UTF8.GetBytes("OFF"));
             })},

            {"LightTurnOn1", (Action)(() => {
                client = new MqttClient("192.168.2.200");
                client.Connect(Guid.NewGuid().ToString());
                client.Publish("gTurn/sobaHostnik/mainLight", Encoding.UTF8.GetBytes("ON"));
             })},

            {"TellMeThatYouLoveMe", (Action)(() => {})},

            {"LightTurnOff1", (Action)(() => {
                client = new MqttClient("192.168.2.200");
                client.Connect(Guid.NewGuid().ToString());
                client.Publish("gTurn/sobaHostnik/mainLight", Encoding.UTF8.GetBytes("OFF"));
             })},
            { "IAmGoingToSleep", (Action)(() => {
                client = new MqttClient("192.168.2.200");
                client.Connect(Guid.NewGuid().ToString());
                client.Publish("gTurn/sobaHostnik/mainLight", Encoding.UTF8.GetBytes("OFF"));
              

             })},
        };

        /*
        Register Custom Cortana Commands from VCD file
        */
        public static async void RegisterVCD()
        {
            StorageFile vcd = await Package.Current.InstalledLocation.GetFileAsync(
                @"CustomVoiceCommandDefinitions.xml");

            await VoiceCommandDefinitionManager
                .InstallCommandDefinitionsFromStorageFileAsync(vcd);
        }

        /*
        Look up the spoken command and execute its corresponding action
        */
        public static void RunCommand(VoiceCommandActivatedEventArgs cmd)
        {
            SpeechRecognitionResult result = cmd.Result;
            string commandName = result.RulePath[0];
            vcdLookup[commandName].DynamicInvoke();
        }
    }
}
