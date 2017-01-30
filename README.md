This is the final project for one of the courses that I have taken at UW. It is a command
line version spinoff of Monoply.

To build the game, run 'make' in the src directory.

After building successfully. Run the binary bb7k from the command line.

More information about this game can be found in bb7k.pdf.

List of Commands:
``` 
roll
```
(used if the player can roll): the player rolls two dice, moves the sum of the two dice and takes action on the square they landed on.
```
next
```
(used if the player cannot roll): give control to the next player.
```
trade <name> <give> <receive>
```
offers a trade to name with the current player offering give
and requesting receive, where give and receive are either amounts of money or a property name.
Responses are accept and reject. For example,
– trade Nomair 500 DC indicates that the current player is willing to give Nomair $500 in
exchange for the DC building
– trade Kirsten DC MC indicates that the current player is willing to give Kirsten DC in exchange
for MC
– trade Sean MC 500 indicates that the current player is willing to give Sean MC in exchange
for $500
```
improve <property> buy/sell
```
attempts to buy or sell an improvement for property.
```
mortgage <property>
```
attempts to mortgage property.
```
unmortgage <property>
```
attempts to unmortgage property.
```
bankrupt
```
player declares bankruptcy. This command is only available when a player must pay more
money then they currently have.
```
assets
```
displays the assets of the current player. Does not work if the player is deciding how to pay Tuition.
```
save <filename>
```
saves the current state of the game (as per the description below) to the given file.