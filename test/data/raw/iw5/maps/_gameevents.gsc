#include common_scripts\utility;
#include maps\_utility;
#include maps\_anim;
#include maps\_audio;
#include maps\_shg_fx;


/*
	GameEvent system
	
	To initialize a new category, call ge_CreateEventManager, with the total cost allowed.
	ge_CreateEvent
	ge_AddEvent
	ge_FlushEvents
	ge_EventFinished

	Event members
		event.priority
		event.class
		event.cost			can be an array
		event.activate_cb
		event.cancel_cb
		event.kill_cb
		event._active
		event._mgr
		event._next
		event._prev
	
	
*/



/*
=============
///ScriptDocBegin
"Name: ge_CreateEventManager( <category>, <availablecost> )"
"Summary: Create a new category of EventManager"
"Module: GameEvent"
"CallOn: "
"MandatoryArg: <category>: The name of the category for this event manager"
"MandatoryArg: <availablecost>: The max amount of active cost for this event manager"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ge_CreateEventManager( category, availablecost, classes )
{
	assert(!isdefined(level._gameEventManagers) || !isdefined(level._gameEventManagers[category]));
	if (!isdefined(level._gameEventManagers))
	{	// start process when first mgr added
		thread _ge_ProcessThread();
	}
	mgr = spawnstruct();
	level._gameEventManagers[category] = mgr;
	mgr.availablecost = availablecost;
	if (isarray(availablecost))
	{
		for (i=0; i<availablecost.size; i++)
			mgr.currentactivecost[i] = 0;
	}
	else
		mgr.currentactivecost = 0;
	mgr.waiting = spawnstruct();
	mgr.active = spawnstruct();
	mgr.classes = classes;
	mgr.index = 0;
}

_ge_CountEvents( list, class )
{
	count = 0;
	if (isdefined(list) && isdefined(list.head))
	{
		list = list.head;
		while (isdefined(list))
		{
			if (!isdefined(class) || (list.class == class))
				count++;
			list = list._next;
		}
	}
	return count;
}

/#
_ge_HideManager( category, mgr )
{
	if (isdefined(mgr.hud_name))
	{
		mgr.hud_name.alpha = 0;
		mgr.hud_index.alpha = 0;
		mgr.hud_waiting.alpha = 0;
		mgr.hud_active.alpha = 0;
		mgr.hud_cost.alpha = 0;
		mgr.hud_bank.alpha = 0;
		
		y = 150;
		foreach (class in mgr.classes)
		{
			mgr.hud_classes[class].alpha = 0;
			y += 10;
		}
	}
}

_ge_ShowManager( category, mgr, idx )
{
	numwaiting = _ge_CountEvents( mgr.waiting );
	numactive = _ge_CountEvents( mgr.active );
	currentcost = mgr.currentactivecost;
	bank = mgr.availablecost;
	BASE_X = 300;
	BASE_Y = 20;
	DELTA_X = 40;
	DELTA_Y = 10;
	x = BASE_X + idx*DELTA_X;
	y = BASE_Y;
	if (!isdefined(mgr.hud_name))
	{
		mgr.hud_name = NewHudElem();
		mgr.hud_name.alignX = "left";
		mgr.hud_name.alignY = "middle";
		mgr.hud_name.x = x;
		mgr.hud_name.y = y;
		mgr.hud_name settext( category );
		mgr.hud_name.label = "GE: ";
		mgr.hud_name.alpha = 0;
		y += DELTA_Y;
		
		mgr.hud_index = NewHudElem();
		mgr.hud_index.alignX = "left";
		mgr.hud_index.alignY = "middle";
		mgr.hud_index.x = x;
		mgr.hud_index.y = y;
		mgr.hud_index.label = "index: ";
		mgr.hud_index.alpha = 0;
		y += DELTA_Y;

		mgr.hud_waiting = NewHudElem();
		mgr.hud_waiting.alignX = "left";
		mgr.hud_waiting.alignY = "middle";
		mgr.hud_waiting.x = x;
		mgr.hud_waiting.y = y;
		mgr.hud_waiting.label = "waiting: ";
		mgr.hud_waiting.alpha = 0;
		y += DELTA_Y;

		mgr.hud_active = NewHudElem();
		mgr.hud_active.alignX = "left";
		mgr.hud_active.alignY = "middle";
		mgr.hud_active.x = x;
		mgr.hud_active.y = y;
		mgr.hud_active.label = "active: ";
		mgr.hud_active.alpha = 0;
		y += DELTA_Y;

		mgr.hud_cost = NewHudElem();
		mgr.hud_cost.alignX = "left";
		mgr.hud_cost.alignY = "middle";
		mgr.hud_cost.x = x;
		mgr.hud_cost.y = y;
		mgr.hud_cost.label = "cost: ";
		mgr.hud_cost.alpha = 0;
		y += DELTA_Y;
		
		mgr.hud_bank = NewHudElem();
		mgr.hud_bank.alignX = "left";
		mgr.hud_bank.alignY = "middle";
		mgr.hud_bank.x = x;
		mgr.hud_bank.y = y;
		mgr.hud_bank.label = "bank: ";
		mgr.hud_bank.alpha = 0;
		y += DELTA_Y;
		
		foreach (class in mgr.classes)
		{
			mgr.hud_classes[class] = NewHudElem();
			mgr.hud_classes[class].alignX = "left";
			mgr.hud_classes[class].alignY = "middle";
			mgr.hud_classes[class].x = x;
			mgr.hud_classes[class].y = y;
			mgr.hud_classes[class].label = class + ": ";
			mgr.hud_classes[class].alpha = 0;
			y += DELTA_Y;
		}
	}
	mgr.hud_name.alpha = 1;
	mgr.hud_waiting SetValue( numwaiting );
	mgr.hud_waiting.alpha = 1;
	mgr.hud_index SetValue( mgr.index );
	mgr.hud_index.alpha = 1;
	mgr.hud_active SetValue( numactive );
	mgr.hud_active.alpha = 1;
	curcost = "";
	if (isarray(currentcost))
	{
		curcost = curcost + currentcost[0];
		for (i=1; i<currentcost.size; i++)
			curcost = curcost + "," + currentcost[i];
	}
	else
		curcost = "" + currentcost;
	mgr.hud_cost SetText( curcost );
	mgr.hud_cost.alpha = 1;
	bnk = "";
	if (isarray(bank))
	{
			bnk = bnk + bank[0];
		for (i=1; i<bank.size; i++)
			bnk = bnk + "," + bank[i];
	}
	else
		bnk = "" + bank;
	mgr.hud_bank SetText( bnk );
	mgr.hud_bank.alpha = 1;
	foreach (class in mgr.classes)
	{
		numwaiting = _ge_CountEvents( mgr.waiting, class );
		numactive = _ge_CountEvents( mgr.active, class );
		numinclass = ""+numwaiting + "    " + numactive;
		mgr.hud_classes[class] SetText(numinclass);
		mgr.hud_classes[class].alpha = 1;
	}
}

_ge_ShowManagers()
{
	debugging = GetDVar("ge_debug");
	while (true)
	{
		if (debugging != GetDvar("ge_debug"))
		{
			debugging = GetDvar("ge_debug");
			if (debugging == "0")
			{	// hide
				foreach (category, mgr in level._gameEventManagers)
				{
					_ge_HideManager(category, mgr);
				}
			}
		}
		if ((debugging != "0") && isdefined(level._gameEventManagers))
		{
			idx=0;
			foreach (category, mgr in level._gameEventManagers)
			{
				_ge_ShowManager(category, mgr, idx);
				idx++;
			}
		}
		wait 0.05;
	}
}

_ge_PrintEvents( list )
{
	if (isdefined(list))
	{
		while (isdefined(list))
		{
			coststr = "";
			if (isarray(list.cost))
			{
				foreach (cost in list.cost)
				{
					coststr = coststr + cost + " ";
				}
			}
			else
				coststr = "" + list.cost + " ";
			
			if (isdefined(list.name))
				println( "  " + list.id + " " + list.priority + " " + coststr + list.class + " " + list.name );
			else
				println( "  " + list.id + " " + list.priority + " " + coststr + list.class );
			list = list._next;
		}
	}
}

_ge_PrintList(category, mgr)
{
	println( category );
	println( " waiting");
	if (isdefined(mgr.waiting) && isdefined(mgr.waiting.head))
		_ge_PrintEvents( mgr.waiting.head );
	println( " active");
	if (isdefined(mgr.active) && isdefined(mgr.active.head))
		_ge_PrintEvents( mgr.active.head );
}

_ge_WaitToShowList()
{
	while (true)
	{
		if (GetDvar("ge_list") != "0")
		{
			SetDvar("ge_list", "0");
			foreach (category, mgr in level._gameEventManagers)
			{
				_ge_PrintList(category, mgr);
			}
			
		}
		wait 0.05;
	}
}

#/

ge_InitDebugging()
{
	/#
	SetDvarIfUninitialized( "ge_debug", "0" );
	SetDvarIfUninitialized( "ge_list", "0" );
	thread _ge_ShowManagers();
	thread _ge_WaitToShowList();
	#/
}




_ge_CanAfford( event, mgr )
{
	if (event.priority >= 100)
		return true;
	if (isarray(mgr.availablecost))
	{
		assert(isarray(mgr.currentactivecost));
		assert(isarray(event.cost));
		for (i=0; i<mgr.availablecost.size; i++)
		{
			assert(isdefined(mgr.currentactivecost[i]));
			assert(isdefined(event.cost[i]));
			if ((event.cost[i] + mgr.currentactivecost[i]) > mgr.availablecost[i])
				return false;
		}
	}
	else
	{
		assert(!isarray(mgr.currentactivecost));
		assert(!isarray(event.cost));
		if ((event.cost + mgr.currentactivecost) > mgr.availablecost)
			return false;
	}
	return true;
}

_ge_AddCostToActive( event, mgr )
{
	if (isarray(mgr.availablecost))
	{
		assert(isarray(mgr.currentactivecost));
		assert(isarray(event.cost));
		for (i=0; i<mgr.availablecost.size; i++)
		{
			assert(isdefined(mgr.currentactivecost[i]));
			assert(isdefined(event.cost[i]));
			mgr.currentactivecost[i] += event.cost[i];
		}
	}
	else
	{
		assert(!isarray(mgr.currentactivecost));
		assert(!isarray(event.cost));
		mgr.currentactivecost += event.cost;
	}
}

_ge_SubtractCostToActive( event, mgr )
{
	if (isarray(mgr.availablecost))
	{
		assert(isarray(mgr.currentactivecost));
		assert(isarray(event.cost));
		for (i=0; i<mgr.availablecost.size; i++)
		{
			assert(isdefined(mgr.currentactivecost[i]));
			assert(isdefined(event.cost[i]));
			mgr.currentactivecost[i] -= event.cost[i];
			assert( mgr.currentactivecost[i] >= 0 );
		}
	}
	else
	{
		assert(!isarray(mgr.currentactivecost));
		assert(!isarray(event.cost));
		mgr.currentactivecost -= event.cost;
		assert( mgr.currentactivecost >= 0 );
	}
}

_ge_ProcessManager( category, mgr )
{
	if (isdefined(mgr.waiting.head))
	{	// we have some pending items
		event = mgr.waiting.head;
		if (_ge_CanAfford( event, mgr ))
		{	// we have enough available to pay for the event or it is a required event (priority >= 100)
			assert(!isdefined(event._prev));
			// remove from waiting list
			mgr.waiting.head = event._next;
			if (isdefined(mgr.waiting.head))
			{
				mgr.waiting.head._prev = undefined;
			}
			else
			{
				mgr.waiting.tail = undefined;
			}
			event._next = undefined;
			// add to active list
			if (isdefined(mgr.active.tail))
			{	// append to the tail
				assert(!isdefined(mgr.active.tail._next));
				mgr.active.tail._next = event;
				event._prev = mgr.active.tail;
				mgr.active.tail = event;
			}
			else
			{	// first entry
				mgr.active.head = event;
				mgr.active.tail = event;
			}
			// Activate it
			event._active = 1;
			_ge_AddCostToActive( event, mgr );
			if (isdefined(event.activate_cb))
				thread [[ event.activate_cb ]]( event );
		}
	}
}

_ge_ProcessThread()
{
	while (true)
	{
		if (isdefined(level._gameEventManagers))
		{
			foreach (category, mgr in level._gameEventManagers)
			{
				_ge_ProcessManager(category, mgr);
			}
		}
		wait 0.05;
	}
}

/*
=============
///ScriptDocBegin
"Name: ge_CreateEvent( <cost>, <priority>, <class> )"
"Summary: Create a new event and initialize some values"
"Module: GameEvent"
"CallOn: "
"MandatoryArg: <cost>: The cost(int) for this event (relative to the availablecost)"
"MandatoryArg: <priority>: The priority(int) for this event (larger number is higher priority)"
"MandatoryArg: <class>: The class (0-31) for this event, used to flush events of a given class"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ge_CreateEvent( cost, priority, class )
{
	event = spawnstruct();
	event.priority = priority;
	event.class = class;
	event.cost = cost;
	event._active = 0;
	return event;
}

/*
=============
///ScriptDocBegin
"Name: ge_AddEvent( <category>, <event> )"
"Summary: Add an event to the waiting list for the category's gameevents"
"Module: GameEvent"
"CallOn: "
"MandatoryArg: <category>: The name of the category"
"MandatoryArg: <event>: The event to add to the priority queue"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ge_AddEvent( category, event)
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	assert(!isarray(mgr.availablecost) || (isarray(event.cost) && (mgr.availablecost.size == event.cost.size)));
	assert(isarray(mgr.availablecost) || !isarray(event.cost));
	assert(IsString(event.class));
	/#
	test = false;	// ensure class is valid
	foreach (class in mgr.classes)
	{
		if (event.class == class)
		{
			test = true;
			break;
		}
	}
	assert(test);
	#/
	event._mgr = mgr;
	event.id = mgr.index;
	mgr.index++;
	
	// find the proper place to insert this in the priority queue
	cur = mgr.waiting.head;
	prv = undefined;
	while (isdefined(cur))
	{
		if (event.priority > cur.priority)
		{
			if (isdefined(prv))
			{
				prv._next = event;
				event._prev = prv;
			}
			else
			{	// first entry in list
				mgr.waiting.head = event;
			}
			event._next = cur;
			cur._prev = event;
			break;
		}
		else
		{
			prv = cur;
			cur = cur._next;
		}
	}
	if (!isdefined(cur))
	{	// reached the end of list
		if (isdefined(prv))
		{
			prv._next = event;
			event._prev = prv;
		}
		else
		{	// first entry in list
			mgr.waiting.head = event;
		}
	}
	if (!isdefined(event._next))
	{
		mgr.waiting.tail = event;
	}
}

_ge_RemoveEvent( list, event )
{
	prv = event._prev;
	nxt = event._next;
	
	if (isdefined(prv))
	{	// remove from middle of list
		assert( prv._next == event);
		prv._next = nxt;
	}
	else
	{
		assert(list.head == event);
		list.head = event._next;
	}
	if (isdefined(nxt))
	{
		assert( nxt._prev == event);
		nxt._prev = prv;
	}
	else
	{
		assert(list.tail == event);
		list.tail = event._prev;
	}
	event._prev = undefined;
	event._next = undefined;
	event._active = -1;
}

_ge_RemoveActiveEvent( mgr, event, call_kill)
{
	if (call_kill && isdefined(event.kill_cb))
	{
		[[event.kill_cb]](event);
	}
	_ge_SubtractCostToActive( event, mgr );
	_ge_RemoveEvent( mgr.active, event );
	event notify("killed");
}

_ge_RemoveWaitingEvent( mgr, event, call_cancel)
{
	if (call_cancel && isdefined(event.cancel_cb))
	{
		[[event.cancel_cb]](event);
	}
	_ge_RemoveEvent( mgr.waiting, event );
}

/*
=============
///ScriptDocBegin
"Name: ge_FlushEvents( <category>, <classes> )"
"Summary: Removes all events (waiting and active) in the category that match with the a class in classes"
"Module: GameEvent"
"CallOn: "
"MandatoryArg: <category>: The name of the category"
"MandatoryArg: <classes>: A single class or array of classes to flush"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ge_FlushEvents( category, classes )
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	event = mgr.waiting.head;
	while (isdefined(event))
	{
		nxt = event._next;	// grab it now, in case we remove it
		if (isarray(classes))
		{
			foreach (class in classes)
			{
				if (event.class == class)
				{
					_ge_RemoveWaitingEvent( mgr, event, true);
					break;
				}
			}
		}
		else
		{
			if (event.class == classes)
				_ge_RemoveWaitingEvent( mgr, event, true);
		}
		event = nxt;
	}
	event = mgr.active.head;
	while (isdefined(event))
	{
		nxt = event._next;	// grab it now, in case we remove it
		if (isarray(classes))
		{
			foreach (class in classes)
			{
				if (event.class == class)
				{
					_ge_RemoveActiveEvent( mgr, event, true);
					break;
				}
			}
		}
		else
		{
			if (event.class == classes)
				_ge_RemoveActiveEvent( mgr, event, true);
		}
		event = nxt;
	}
}

/*
=============
///ScriptDocBegin
"Name: ge_EventFinished( <event> )"
"Summary: Tells the appropriate eventmanager that this event is finished and should be removed from the active list"
"Module: GameEvent"
"CallOn: "
"MandatoryArg: <event>: The event that just finished"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ge_EventFinished( event, delay )
{
	if (isdefined(delay))
		wait delay;
	if (!isdefined(event))
		return;
	if (event._active < 0)
		return;	// already removed (probably by a flush)
	mgr = event._mgr;
	assert(isdefined(mgr));
	if (event._active)
	{
		_ge_RemoveActiveEvent( mgr, event, false );
	}
	else
	{
		_ge_RemoveWaitingEvent( mgr, event, false );
	}
}


ge_FindNextEventByName( event, name )
{
	if (isdefined(event))
	{
		while (isdefined(event))
		{
			if (isdefined(event.name) && (event.name == name))
				break;
			event = event._next;
		}
	}
	return event;
}

ge_FindWaitingEventByName( category, name )
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	event = mgr.waiting.head;
	return ge_FindNextEventByName( event, name );
}

ge_FindActiveEventByName( category, name )
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	event = mgr.active.head;
	return ge_FindNextEventByName( event, name );
}

_ge_CountEventsByName( event, name )
{
	count = 0;
	if (isdefined(event))
	{
		while (isdefined(event))
		{
			if (isdefined(event.name) && (event.name == name))
				count++;
			event = event._next;
		}
	}
	return count;
}

ge_CountWaitingEventByName( category, name )
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	event = mgr.waiting.head;
	return _ge_CountEventsByName( event, name );
}

ge_CountActiveEventByName( category, name )
{
	mgr = level._gameEventManagers[category];
	assert(isdefined(mgr));
	event = mgr.active.head;
	return _ge_CountEventsByName( event, name );
}

/****************************************************************************************************/
// specific categories


// Generic Effect
ge_AddEffect( fxname, lifetime, cost, priority, class )
{
	if (!isdefined(lifetime))
		lifetime = -1;	// default duration is infinite
	event = _ge_AddEffectEvent( cost, priority, class );
	event.fxname = fxname;
	event.lifetime = lifetime;
	return event;
}

_ge_AddEffectEvent( cost, priority, class )
{
	if (!isdefined(cost))
		cost = 100;	// default cost
	if (!isdefined(priority))
		priority = 100;	// default priority
	if (!isdefined(class))
		class = 1;	// default class
	event = ge_CreateEvent( cost, priority, class );
	event.activate_cb = ::_ge_ActivateEffect;
	event.cancel_cb = ::_ge_CancelEffect;
	event.kill_cb = ::_ge_KillEffect;
	ge_AddEvent( "fx", event);
	return event;
}

_ge_ActivateEffect( event )
{	// start the effect
	event endon("killed");
}

_ge_CancelEffect( event )
{	// since we didn't start anything before activation, we don't need to do anything
}

_ge_KillEffect( event )
{	// kill the active effect (don't need to remove it, since caller will)
}

// Generic Exploder
ge_AddExploder( fxid, lifetime, cost, priority, class )
{
	if (!isdefined(lifetime))
		lifetime = -1;	// default duration is infinite
	event = _ge_AddExploderEvent( cost, priority, class );
	event.fxnid = fxid;
	event.lifetime = lifetime;
}

_ge_AddExploderEvent( cost, priority, class )
{
	if (!isdefined(cost))
		cost = 100;	// default cost
	if (!isdefined(priority))
		priority = 100;	// default priority
	if (!isdefined(class))
		class = 1;	// default class
	event = ge_CreateEvent( cost, priority, class );
	event.activate_cb = ::_ge_ActivateExploder;
	event.kill_cb = ::_ge_KillExploder;
	ge_AddEvent( "fx", event);
	return event;
}

_ge_ActivateExploder( event )
{	// start the effect
	assert(isdefined(event.fxid));
	event endon("killed");
	exploder(event.fxid);
	if (isdefined(event.lifetime))
	{
		if (event.lifetime == 0)
		{
			ge_EventFinished("fx", event);
		}
		else if (event.lifetime > 0)
		{
			wait event.lifetime;
			ge_EventFinished("fx", event);
		}
	}
	// infinite lifetime
}

_ge_KillExploder( event )
{	// kill the active effect (don't need to remove it, since caller will)
}

// Generic notifies
ge_AddNotify( category, activate_msg, cancel_msg, kill_msg, cost, priority, class, name )
{
	event = ge_CreateEvent( cost, priority, class );
	event.activate_msg = activate_msg;
	event.cancel_msg = cancel_msg;
	event.kill_msg = kill_msg;
	event.activate_cb = ::_ge_ActivateNotify;
	event.cancel_cb = ::_ge_CancelNotify;
	event.kill_cb = ::_ge_KillNotify;
	event.name = name;	// optional parameter
	ge_AddEvent( category, event);
	return event;
}
ge_AddNotifyWait( category, activate_msg, cancel_msg, kill_msg, cost, priority, class, name )
{
	event = ge_AddNotify( category, activate_msg, cancel_msg, kill_msg, cost, priority, class, name );
	event waittill( activate_msg );
	return event;
}

_ge_Notify( event, msg )
{
	event notify( msg );
	if (isdefined(event.ent))
		event.ent notify( msg );
}

_ge_ActivateNotify( event )
{	// Do the activate notify
	_ge_Notify( event, event.activate_msg );
}

_ge_CancelNotify( event )
{	// Do the cancel notify
	_ge_Notify( event, event.cancel_msg );
}

_ge_KillNotify( event )
{	// Do the kill notify
	_ge_Notify( event, event.kill_msg );
}

ge_AddFxNotify( activate_msg, cancel_msg, kill_msg, cost, priority, class )
{
	return ge_AddNotify( "fx", activate_msg, cancel_msg, kill_msg, cost, priority, class );
}

ge_AddFxNotifyWait( activate_msg, cancel_msg, kill_msg, cost, priority, class, name )
{
	return ge_AddNotifyWait( "fx", activate_msg, cancel_msg, kill_msg, cost, priority, class, name );
}

/*
  event = ge_AddFxNotify( activate_msg, cancel_msg, kill_msg, cost, priority, class );
  event.ent = self;
  self endon( cancel_msg );
  self waittill( activate_msg );
  self.endon( kill_msg );
  // do the fx work.  If necessary, thread a function waiting for kill_msg
*/

ge_AddAlways( category, cost, priority, class )
{
	event = ge_CreateEvent( cost, priority, class );
	ge_AddEvent( category, event);
}
